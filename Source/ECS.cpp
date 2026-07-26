#include "ECS.h"

FEntity::FEntity(FEntityId EntityId) : Id(EntityId)
{
}

FEntity::~FEntity()
{
    FEntityFactory::DestroyEntity(Id);
}

TUnique<FEntity> FEntityFactory::CreateEntity()
{
    static FEntityId EntityId { INVALID_ENTITY_ID };
    FEntityId NextEntityId { INVALID_ENTITY_ID };
    if (!FreeEntityIds.empty())
    {
        NextEntityId = *FreeEntityIds.begin();
        FreeEntityIds.erase(NextEntityId);
    }
    if (NextEntityId == INVALID_ENTITY_ID)
    {
        NextEntityId = ++EntityId;
    }
    assert(NextEntityId != INVALID_ENTITY_ID);
    return std::make_unique<FEntity>(NextEntityId);
}

void FEntityFactory::DestroyEntity(FEntityId EntityId)
{
    if (EntityId == INVALID_ENTITY_ID || FreeEntityIds.find(EntityId) != FreeEntityIds.end())
    {
        return;
    }
    for (const auto& ComponentDeleter : ComponentDeleters)
    {
        ComponentDeleter(EntityId);
    }
    FreeEntityIds.insert(EntityId);
}

TSet<FEntityId> FEntityFactory::FreeEntityIds {};
TSet<FEntityFactory::FComponentDeleter> FEntityFactory::ComponentDeleters {};
