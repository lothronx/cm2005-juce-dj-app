# OOP Final Project Report

Name: Yue Wu

Student ID: 210312838

## Introduction

![The user interface of Otodecks](0.png)

Otodecks is a DJ application that allows users to mix and play audio files. It provides users with the following features:

- Load audio files into two audio players either by dragging and dropping or via the "Load" button.

- Control the playback of a track via the "Play/Pause" button.

- Loop a track or to stop it from looping via the "Loop" button.

- Blend two tracks together by adjusting their volumes via a crossfader.

- Adjust the playback position, speed, volume, as well as boost/cut the bass, mid and treble of each track independently via sliders.

- Get visual feedback on the file name, elapsed time, playback state, the current position in the waveform, and the volume level in real-time via GUI elements such as labels, progress bars, and jog wheels, and VU meters.

The source code structure is as follows:

![The code structure of Otodecks](2.png)

The GUI component classes are marked in red. The `MainComponent` comprises two `DeckGUI`s and one `Crossfader`. Each DeckGUI contains 6 sub-components: `WaveformDisplay`, `JogWheel`, `TransportControls`, `SpeedSlider`, `Knobs`, and `VUMeter`. The GUI component classes are responsible for rendering the GUI and handling user events and state changes.

The audio source class is marked in green. The `AudioPlayer` class handles the track loading, playback, and manipulation all in one place. The GUI component classes communicate with the AudioPlayer class and call its public member functions to manipulate the audio tracks.

The look and feel class is marked in yellow. The `CustomLookAndFeel` class is responsible for customizing the appearance of the GUI components.

The code structure is also reflected in the user interface layout. The following low-fidelity prototype shows the one-to-one correspondence between the GUI component classes and the user interface layout (except logo, which is too easy to implement to be a class):

![The low-fidelity prototype of Otodecks](1.png)

## R1: Basic program functionality

### R1A: can load audio files into audio players (Load button)

Otodecks allows users to load audio files into two audio players either by dragging and dropping or via the "Load" button.

The code for the drag and drop feature remains unchanged in the `DeckGUI` class.

The "Load" button code is refactored into the `TransportControls` class with one new feature:

Now, the "Load" button is upgraded into a toggle button with color indication of whether the audio file is loaded. If no file is loaded, the "Load" button is colored; otherwise, it is grayed out.

The button state is not toggled by user clicks, by rather managed by a change listener. The `TransportControls` object registers itself as a change listener for the `DJAudioPlayer` object. After `DJAudioPlayer` finishes loading the audio file, it sends a message to all its change listeners. The `TransportControls` class receives this message and updates the state of the "Load" button accordingly.

The button color is handled by the `CustomLookAndFeel` class.

### R1B: can play two or more tracks (Play/Pause button)

Otodecks allows users to play two tracks simultaneously. The "Play/Pause" button in each `TransportControls` class is responsible for controlling the playback of a track.

Comparing to the starter code, I combine the "Play" and "Stop" buttons into one button. The button state is toggle-able. The implementation of the "Play/Pause" button is similar to that of the "Load" button.

It is worth noting that in `DJAudioPlayer` class, `play()` function broadcasts a message to toggle the button state, but the `stop()` function does not. This is because not only user clicks can pause a track, but a track can also naturally stop when it reaches the end. If we only notify the "Play/Pause" button of the stop event when the user clicks the "Stop" button and calls the `stop()` function, the button state will not be updated when the track stops naturally. Thus, the better way to notify the "Play/Pause" button of the stop event is to set a timer in the `DJAudioPlayer` class. The timer will keep checking whether the track stops and send a message to the `TransportControls` class when it does.

### R1C: can mix the tracks by varying each of their volumes (Volume slider)

Otodecks allows users to control the volume of each track independently via the volume sliders. Users can also adjust the volume ratio of the two tracks via the crossfader.

The code for the volume slider is refactored into the `Knobs` class. The volume slider ranges from 0% to 100%. It allows users to adjust the volume of the track from total silence to the maximum volume. The initial volume is set to 50%.

A new component `Crossfader` is added. The `Crossfader` class allows users to adjust the volume ratio of the two tracks from 0% : 100% to 100% : 0%. The initial volume ratio is set to 50% : 50%.

The volume sliders are connected to the crossfader. Moving the crossfader will also move the volume sliders. Moving the volume sliders, however, will not move the crossfader. This allows users to not only adjust the volume balance of the two tracks all in once, but also fine tune the volume of each track independently. 

### R1D: can speed up and slow down the tracks (Speed slider)

Otodecks allows users to adjust the playback speed of each track independently via the speed sliders.

The code for the speed slider is refactored into the `SpeedSlider` class. The speed slider ranges from -50% to 50%. It allows users to speed up or slow down the track by 50% at most. The initial value is set to 0%, which means playing the track at its original speed.

## R2 Customizing the user interface

### R2A: GUI layout is significantly different from the basic DeckGUI shown in class



### R2B: GUI code has at least one event listener that was not in the original codebase seen in class.

## R3

Research and technical information covering how you identified, analysed and implemented a new feature that you found in another DJ application (R3)
• R3: Investigate and implement a new feature inspired by a real DJ program.

◦ To complete this requirement, you need to research DJ applications and identify a feature to implement. You do not need to run the other DJ applications - you can use YouTube and other resources to find out what features other DJ applications have.

◦ Implement a DJ-related feature that you have seen in another DJ program.

◦ In your report you should present a screenshot and analysis of another DJ application and the feature you want to implement. Then you should explain how you have engineered this feature, talking about the classes and other OOP constructs you used to do the work.

◦ Finally, you should include the feature in the code and video that you submit.

## Conclusion
