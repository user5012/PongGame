#include <SFML/Audio.hpp>

class Audio  
{  
public:  
   Audio()  
       : soundHit(bufferHit), soundEnd(bufferEnd), soundWallHit(bufferWallHit)  
   {  
       // Load sound buffers  
       if (!bufferHit.loadFromFile("hit.wav")) {  
           throw std::runtime_error("Failed to load hit.wav");  
       }  
       if (!bufferEnd.loadFromFile("end.wav")) {  
           throw std::runtime_error("Failed to load end.wav");  
       }  
       if (!bufferWallHit.loadFromFile("wall_hit.wav")) {  
           throw std::runtime_error("Failed to load wall_hit.wav");  
       }  
       // No need to call setBuffer; already set by constructor  
   }

   

   sf::Music& getMusic() { return this->music; }  
   sf::Sound& getSoundHit() { return this->soundHit; }  
   sf::Sound& getSoundEnd() { return this->soundEnd; }  
   sf::Sound& getSoundWallHit() { return this->soundWallHit; }  

   void PlayMusicAndStartLoop() {  
       this->music.play();  
       this->music.setLooping(true);  
   }  
   void StopMusicAndLoop() {  
       this->music.stop();  
       this->music.setLooping(false);  
   }  

private:  
   sf::Music music;  
   sf::SoundBuffer bufferHit, bufferEnd, bufferWallHit;  
   sf::Sound soundHit, soundEnd, soundWallHit;  
};
