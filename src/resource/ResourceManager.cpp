
#include "ResourceManager.hpp"

using namespace ci;
using namespace dowa;

//Audio Resource

hidden::AudioResource::AudioResource() {
  //Tweak : Place the insert function where you will use the audio files
  //It will work the same way
  //inserting all the audio files here may cause the program to be slower

  //Use it Right : When you insert some audio file, do a fail check with it
  //the insert function returns a bool value when executed

  insert("sound/bgm/menu.wav", AudioKey::Menu);
  insert("sound/bgm/cinderella/town.wav", CinderellaAudioKey::Town);
  insert("sound/bgm/cinderella/castle.wav", CinderellaAudioKey::Castle);

  insert("sound/se/gamestart.wav", AudioKey::GameStartSE);
  insert("sound/se/stageselected.wav", AudioKey::StageSelectSE);
}

bool hidden::AudioResource::insert(std::string path, int key) {
  hidden::AudioIterator it = mMappedResource.find(key);

  if (it != mMappedResource.end()) {
    return false;
  }

  hidden::Audio temp;

  auto ctx = audio::Context::master();

  audio::SourceFileRef sourceFile = audio::load(ci::app::loadAsset(path));
  audio::BufferRef buffer = sourceFile->loadBuffer();
  temp.bgm = ctx->makeNode(new audio::BufferPlayerNode(buffer));
  temp.gain = ctx->makeNode(new audio::GainNode(1.0f));

  temp.bgm >> temp.gain >> ctx->getOutput();

  ctx->enable();

  mMappedResource.insert(std::make_pair(key,temp));

  return true;
}

hidden::Audio hidden::AudioResource::get(int key) {
  return mMappedResource.find(key)->second;
}

//Audio Resource

//Texture Resource

hidden::TextureResource::TextureResource() {
  //Tweak : Place the insert function where you will use the textures
  //It will work the same way
  //inserting all the textures here may cause the program to be slower

  //Use it Right : When you insert some texture, do a fail check with it
  //the insert function returns a bool value when executed

  insert("object/DownVeil.png", TextureKey::DownVeil);
  insert("object/VeilSpace.png", TextureKey::VeilSpace);

  //Tweak it: Change the CinderellaTextureKey to something more readable
  //Make it shorter with typedef
  insert("character/cinderella/1.png", CinderellaTextureKey::CharacterStatic);
  insert("character/cinderella/2.png", CinderellaTextureKey::CharacterLeft);
  insert("character/cinderella/3.png", CinderellaTextureKey::CharacterRight);
  insert("background/gameMain/cinderella/1.jpg", CinderellaTextureKey::House);
  insert("background/gameMain/cinderella/2.jpg", CinderellaTextureKey::Forest);
  insert("background/gameMain/cinderella/3.jpg", CinderellaTextureKey::Town3Houses);
  insert("background/gameMain/cinderella/4.jpg", CinderellaTextureKey::TownBridge);
  insert("background/gameMain/cinderella/5.png", CinderellaTextureKey::Town2Houses);
  insert("background/gameMain/cinderella/6.png", CinderellaTextureKey::Bridge);
  insert("background/gameMain/cinderella/7.jpg", CinderellaTextureKey::Castle);

  // result�p��resource

  insert("background/result/Back.jpg", TextureKey::Back);
  insert("background/result/Retry.jpg", TextureKey::Retry);
  insert("background/result/Select.jpg", TextureKey::Select);
  insert("background/result/Fin.jpg", TextureKey::Fin);
  insert("background/result/Font.png", TextureKey::Font);
}

bool hidden::TextureResource::insert(std::string path, int key) {
  hidden::TextureIterator it = mMappedResource.find(key);

  if (it != mMappedResource.end()) {
    return false;
  }

  gl::Texture temp;

  temp = gl::Texture(loadImage(ci::app::loadAsset(path)));

  mMappedResource.insert(std::make_pair(key,temp));

  return true;
}

ci::gl::Texture hidden::TextureResource::get(int key) {
  return mMappedResource.find(key)->second;
}

//Texture Resource

//Resource Manager

void ResourceManager::enable(){
  audio();
  texture();
}

//Resource Manager