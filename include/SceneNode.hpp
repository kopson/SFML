#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <Category.hpp>

#include <cassert>
#include <memory>
#include <vector>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

struct Command;
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
        SceneNode();

        void attachChild(Ptr child);
        Ptr detachChild(const SceneNode& node);
        void update(sf::Time dt);
        sf::Transform getWorldTransform() const;
        sf::Vector2f getWorldPosition() const;
		void onCommand(const Command& command, sf::Time dt);
		virtual unsigned int getCategory() const;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void updateCurrent(sf::Time dt);
        void updateChildren(sf::Time dt);

        std::vector<Ptr> mChildren;
        SceneNode* mParent;
};

#endif // SCENENODE_HPP
