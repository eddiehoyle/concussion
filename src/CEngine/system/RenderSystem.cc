#include "RenderSystem.hh"
#include "GLBuffer.hh"

namespace concussion {

namespace system {

RenderSystem::RenderSystem() :
        m_Window( nullptr ),
        m_ActiveCamera( nullptr ) {

    // create global vertex and index buffer
    this->m_VertexBuffer = new VertexBuffer( GLOBAL_VERTEX_BUFFER_SIZE );
    this->m_IndexBuffer = new IndexBuffer( GLOBAL_INDEX_BUFFER_SIZE );
}


RenderSystem::~RenderSystem() {

//    for (size_t i = 0; i < this->m_BufferedShapes.size(); ++i)
//    {
//        delete this->m_BufferedShapes[i];
//        this->m_BufferedShapes[i] = nullptr;
//    }
//    this->m_BufferedShapes.clear();

//    for (auto it : this->m_RenderableGroups)
//    {
//        it.first.Delete();
//        it.second.clear();
//    }

    // free global vertex and index buffer
    delete this->m_VertexBuffer;
    this->m_VertexBuffer = nullptr;

    delete this->m_IndexBuffer;
    this->m_IndexBuffer = nullptr;
}


void RenderSystem::OnGameObjectCreated( AbstractEntity* entity ) {

    // Get Entity
//    AbstractEntity* entity = CNCEngine->GetEntityManager()->GetEntity(entity->getID());
//    CNC_ASSERT(entity != nullptr && "Failed to retrieve entity by id!");
//
//    // get entities material and shape component
//    TransformComponent*	transformComponent	= entity->getComponent<TransformComponent>();
//    MaterialComponent*	materialComponent	= entity->getComponent<MaterialComponent>();
//    ShapeComponent*		shapeComponent		= entity->getComponent<ShapeComponent>();
//
//    // If there is one of the components missing we can stop, there is nothing todo for the renderer
//    if ( transformComponent == nullptr ||
//         materialComponent == nullptr ||
//         shapeComponent == nullptr ) {
//        return;
//    }
//
//    // Set shape's data buffer indices
//    SetShapeBufferIndex(shapeComponent);
//
//    // Register entity as new renderable
//    RegisterRenderable( entity );
}

void RenderSystem::SetShapeBufferIndex( ShapeComponent* shapeComponent ) {

}

void RenderSystem::RegisterRenderable( AbstractEntity* entity ) {

}

}

}
