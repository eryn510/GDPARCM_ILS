#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"

class IExecutionEvent;
class ThreadPool;
class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;

public:
	static TextureManager* getInstance();
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadStreamingAssets();
	void loadSingleStreamAsset(int index, IExecutionEvent* executionEvent); //loads a single streaming asset based on index in directory
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getStreamTextureFromList(const int index);
	std::vector<sf::Texture*> getStreamingTextures();
	int getNumLoadedStreamTextures() const;
	int getStreamingCount();

private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	ThreadPool* threadPool;
	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;

	const std::string STREAMING_PATH = "Media/Streaming/";
	const std::string FRAMES_PATH = "Media/Frames/";
	int streamingAssetCount = 0;

	void countStreamingAssets();
	void instantiateAsTexture(String path, String assetName, bool isStreaming);

	friend class StreamAssetLoader;

};