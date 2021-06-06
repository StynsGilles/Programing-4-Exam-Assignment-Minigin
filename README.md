# Programing-4-Exam-Assignment-Minigin

For my Exam assignment for the course Programming 4 at the degree Digital Arts & Entertainment: Game Development, I got a start framework called Minigin from which I had to create my own 2D engine.

## GameObjects with Components

Every object in the game is a gameobject which components (inherited from BaseComponent) can get attached to, to give it functionality.
The engine already has a couple components that are useable in virtually any game made with the engine.
These are:
* ClickComponent: is an abstract class that checks if the user clicked in the gameobject's texture. What happens on click, must be implemented in the inherited class.
* FPSComponent: updates the gameobject, that this component is attached to, its textcomponent to show the current fps.
* RenderComponent: renders a texture.
* TextComponent: renders text, this text can be modified at runtime.
* SubjectComponent: to notify observers.

## Scenes and SceneManager

My implementation of Minigin supports multiple scenes and the ability to switch between these scenes easily.
Every scene also has its own input.

## Command

Commands get bound to inputs that get checked in the inputmanager.
A command can easily be implemented by inheriting from the Command class and do its own thing.
The inputmanager uses SDL_Event and xinput to check for inputs.

## Observer

To prevent checking every frame for certain things, like health and score for example, I used the observer pattern.
A gameobject can get a SubjectComponent attached that will notify all the observers it knows of events that happened.

## File parsing

The engine uses rapidjson to parse a given file into a rapidjson document and returns this to the user to handle the data.

## Audio

I used SDL2 audio to handle audio, this plays .wav files. This also runs on a separate thread.
