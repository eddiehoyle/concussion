#ifndef CONCUSSION_RENDERSYSTEM_HH
#define CONCUSSION_RENDERSYSTEM_HH

#include "Platform.hh"
#include "AbstractEntity.hh"
#include "TransformComponent.hh"
//#include "ShapeComponent.hh"
//#include "MaterialComponent.hh"

namespace concussion {

using GameObjectID = ObjectID;
using RenderableGroupID = ObjectID;

class Window;

class VertexBuffer;
class IndexBuffer;
class AbstractGameCamera;

class ShapeComponent;
class MaterialComponent;

class RenderableGroup {};

namespace system {

class RenderSystem {

    static constexpr size_t		GLOBAL_VERTEX_BUFFER_SIZE { 8388608 /* 8 MB */ };
    static constexpr size_t		GLOBAL_INDEX_BUFFER_SIZE  { 8388608 /* 8 MB */ };

//    static inline const RenderableGroupID CreateRenderableGroupID( MaterialComponent* material,
//                                                                   ShapeComponent* shape) {
//        return ((material->GetMaterialID() << 16) | shape->GetShapeID());
//    }

//    using BufferedShapes = std::vector<ShapeBufferIndex*>;

    struct Renderable {

        GameObjectID			m_GameObjectId;
        AbstractEntity*			m_GameObject;

        TransformComponent*		m_TransformComponent;
        ShapeComponent*			m_ShapeComponent;
        MaterialComponent*		m_MaterialComponent;


        Renderable( AbstractEntity* entity,
                    TransformComponent* transform,
                    MaterialComponent* material,
                    ShapeComponent* shape) :
                m_GameObjectId(entity->getID()),
                m_GameObject(entity),
                m_TransformComponent(transform),
                m_MaterialComponent(material),
                m_ShapeComponent(shape)
        {}

        ~Renderable() {
            this->m_GameObjectId = 0;
            this->m_GameObject = nullptr;
            this->m_TransformComponent = nullptr;
            this->m_MaterialComponent = nullptr;
            this->m_ShapeComponent = nullptr;
        }
    };

    using RenderableList = std::list< Renderable >;
    using RenderableGroups = std::unordered_map< RenderableGroup, RenderableList >;

private:

    // Application window
    Window*			m_Window;

    // Render context
//    Context		m_Context;

    // Global Vertex and Index Buffer
    VertexBuffer*		m_VertexBuffer;
    IndexBuffer*		m_IndexBuffer;

    // Keeps track of already buffered shapes
//    BufferedShapes		m_BufferedShapes;

    // A set of all currently registered randerable entities
//    RenderableGroups	m_RenderableGroups;

    // Active Camera
    AbstractGameCamera*		m_ActiveCamera;

private:

    void InitializeOpenGL();
    void TerminateOpenGL();

    void SetShapeBufferIndex( ShapeComponent* shapeComponent );
    void RegisterRenderable( AbstractEntity* entity );

    void OnGameObjectCreated( AbstractEntity* event);
    void OnGameObjectDestroyed( AbstractEntity* event);

public:

    RenderSystem();
    ~RenderSystem();

    void PreUpdate( float delta );
    void Update( float delta );
    void PostUpdate( float delta );

};

}

}

#endif // CONCUSSION_RENDERSYSTEM_HH
