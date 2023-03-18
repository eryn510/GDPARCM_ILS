#pragma once
#include "AObject.h"
#include "IExecutionEvent.h"

class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay: public AObject, public IExecutionEvent
{
public:
	TextureDisplay();
	void Update(sf::Time deltaTime);

	// Inherited via AObject
	virtual void initialize() override;

	virtual void processInput(sf::Event event) override;

	// Inherited via IExecutionEvent
	virtual void onFinishedExecution() override;

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 100.0f; //greatly reduce streaming load delay to demonstrate performance drop.
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;
	
	int texIndex = 0;
	int loadedTex = 0;

	void checkProgress();

};

