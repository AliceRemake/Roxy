#pragma once

// ECS Framework. Not For Multi Thread For Now.


#include "Core.h"

// Why Unsigned And 0 ? This Is Because:
// 1. We Can Use EntityId != INVALID_ENTITY_ID
// 2. We Do Not Iter Through Entity ID Often
// 3. We Can Have A Larger Valid ID Range
using FEntityId = UInt32; /* Strong Type */
constexpr FEntityId INVALID_ENTITY_ID { 0 };

template<typename T>
class TSparseSet
{
public:
    T* GetWriteComponent(FEntityId EntityId)
    {
        if (EntityId != INVALID_ENTITY_ID)
        {
            ExpandSparse(EntityId);
            if (Sparse.at(EntityId - 1) != INVALID_INDEX)
            {
                return Dense.at(Sparse.at(EntityId - 1)).Component.get();
            }
        }
        return {};
    }

    const T* GetReadComponent(FEntityId EntityId) const
    {
        if (EntityId != INVALID_ENTITY_ID && EntityId <= Sparse.size() && Sparse.at(EntityId - 1) != INVALID_INDEX)
        {
            return Dense.at(Sparse.at(EntityId - 1)).Component.get();
        }
        return {};
    }

    bool HasComponent(FEntityId EntityId) const
    {
        return EntityId != INVALID_ENTITY_ID
            && EntityId <= Sparse.size()
            && Sparse.at(EntityId - 1) != INVALID_INDEX;
    }

    // Component Is Designed One Type Per Entity. Newer Replace Older.
    void NewComponent(FEntityId EntityId, TUnique<T> Component)
    {
        if (EntityId != INVALID_ENTITY_ID && Component != nullptr)
        {
            ExpandSparse(EntityId);
            if (Sparse.at(EntityId - 1) != INVALID_INDEX)
            {
                Dense.at(Sparse.at(EntityId - 1)).Component = std::move(Component);
            }
            else
            {
                assert(Dense.size() <= std::numeric_limits<FIndex>::max());
                Sparse.at(EntityId - 1) = Dense.size();
                Dense.emplace_back(FDenseElement
                {
                    .EntityId  = EntityId,
                    .Component = std::move(Component),
                });
            }
        }
    }

    void DelComponent(FEntityId EntityId)
     {
        if (!Dense.empty() && Swap(EntityId, Dense.back().EntityId))
        {
            // This Means We Always Delete The Last One
            assert(Sparse.at(EntityId - 1) + 1 == Dense.size());
            Sparse.at(EntityId - 1) = INVALID_INDEX;
            Dense.pop_back();
        }
     }

    template<typename TFunc> void ReadEachComponent(TFunc&& Func) const  // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        for (const auto& [_, Component] : Dense)
        {
            assert(Component.get() != nullptr);
            Func(std::as_const(*Component));
        }
    }

    template<typename TFunc> void WriteEachComponent(TFunc&& Func)  // NOLINT(cppcoreguidelines-missing-std-forward)
    {
        for (const auto& [_, Component] : Dense)
        {
            assert(Component.get() != nullptr);
            Func(*Component);
        }
    }

protected:
    void ExpandSparse(FEntityId EntityId)
    {
        if (EntityId > Sparse.size())
        {
            Sparse.resize(EntityId, INVALID_INDEX);
        }
    }

    bool /* Succeed */ Swap(FEntityId Lhs, FEntityId Rhs)
    {
        if (Lhs == INVALID_ENTITY_ID || Rhs == INVALID_ENTITY_ID)
        {
            return false;
        }
        ExpandSparse(Lhs > Rhs ? Lhs : Rhs);
        if (Sparse.at(Lhs - 1) == INVALID_INDEX || Sparse.at(Rhs - 1) == INVALID_INDEX)
        {
            return false;
        }
        if (Lhs == Rhs)
        {
            return true;
        }
        std::swap(Sparse.at(Lhs - 1), Sparse.at(Rhs - 1));
        std::swap(Dense.at(Sparse.at(Lhs - 1)), Dense.at(Sparse.at(Rhs - 1)));
        assert(Dense.at(Sparse.at(Lhs - 1)).EntityId == Lhs);
        assert(Dense.at(Sparse.at(Rhs - 1)).EntityId == Rhs);
        return true;
    }

    struct FDenseElement
    {
        FEntityId  EntityId  { INVALID_ENTITY_ID };
        TUnique<T> Component { nullptr };
    };

    TArray<FIndex>        Sparse {};
    TArray<FDenseElement> Dense  {};
};

class FEntity
{
public:
    explicit FEntity(FEntityId EntityId);
    ~FEntity();
    FEntity(const FEntity&) = delete;
    FEntity& operator=(const FEntity&) = delete;
    FEntity(FEntity&&) = delete;
    FEntity& operator=(FEntity&&) = delete;

    template<typename TComponent>
    const TComponent* GetReadComponent() const
    {
        return GetSparseSet<TComponent>().GetReadComponent(Id);
    }

    template<typename TComponent>
    TComponent* GetWriteComponent()
    {
        return GetSparseSet<TComponent>().GetWriteComponent(Id);
    }

    template<typename TComponent> static TSparseSet<TComponent>& GetSparseSet()
    {
        static TSparseSet<TComponent> SparseSet;
        return SparseSet;
    }

protected:
    FEntityId Id { INVALID_ENTITY_ID };
};

class FComponent
{
public:
    virtual ~FComponent() = default;
    FComponent(const FComponent&) = delete;
    FComponent& operator=(const FComponent&) = delete;
    FComponent(FComponent&&) = delete;
    FComponent& operator=(FComponent&&) = delete;
};

class FSystem
{
public:
    virtual ~FSystem() = default;
    FSystem(const FSystem&) = delete;
    FSystem& operator=(const FSystem&) = delete;
    FSystem(FSystem&&) = delete;
    FSystem& operator=(FSystem&&) = delete;
};

class FEntityFactory final
{
public:
    using FComponentDeleter = void (*)(FEntityId);

    template<typename TComponent>
    static void RegisterComponent()
    {
        ComponentDeleters.insert([](FEntityId EntityId) -> void
        {
            FEntity::GetSparseSet<TComponent>().DelComponent(EntityId);
        });
    }

    static TUnique<FEntity> CreateEntity();

    static void DestroyEntity(FEntityId EntityId);

private:
    static TSet<FEntityId> FreeEntityIds;
    static TSet<FComponentDeleter> ComponentDeleters;
};
