#include <World.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
, mPlayerCar(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
	// Scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	// Move the player sidewards (plane scouts follow the main vehicle)
	sf::Vector2f position = mPlayerCar->getPosition();
	sf::Vector2f velocity = mPlayerCar->getVelocity();

	// If player touches borders, flip its X velocity
	if (position.x <= mWorldBounds.left + 150.f
	 || position.x >= mWorldBounds.left + mWorldBounds.width - 150.f)
	{
		velocity.x = -velocity.x;
		mPlayerCar->setVelocity(velocity);
	}

	// Apply movements
	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextures.load(Textures::Eagle, "res/textures/Eagle.png");
	mTextures.load(Textures::Raptor, "res/textures/Raptor.png");
	mTextures.load(Textures::Desert, "res/textures/Desert.png");
}

void World::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's vehicle
	std::unique_ptr<Vehicle> leader(new Vehicle(Vehicle::Eagle, mTextures));
	mPlayerCar = leader.get();
	mPlayerCar->setPosition(mSpawnPosition);
	mPlayerCar->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// Add two escorting vehicles, placed relatively to the main plane
	std::unique_ptr<Vehicle> leftEscort(new Vehicle(Vehicle::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerCar->attachChild(std::move(leftEscort));

	std::unique_ptr<Vehicle> rightEscort(new Vehicle(Vehicle::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerCar->attachChild(std::move(rightEscort));
}
