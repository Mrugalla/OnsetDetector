This is my onset detector project. I want to invite you all to contribute to it,
so that we can together enjoy great onset detection!

Here's what you can do with it:

a) You can build the given JUCE project and use it as VST3 plugin.
The plugin produces audio impulses and sends specific MIDI sysex messages on onsets,
so you can let another plugin interpret the events.

b) You can download the algorithm's code to get a nice starting point for a
working onset detector. please feel free to send pull requests if you make improvements! :)

The algorithm itself has a permissive MIT license, but the JUCE example uses GPL, because it's JUCE.
So if you wanna contribute to the algorithm, please do so on the MIT one.
