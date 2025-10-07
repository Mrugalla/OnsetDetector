I've been working on an onset detection algorithm and now I made it a seperate project so that

a) devs can build it and use it as VST3 plugin.
the plugin produces audio impulses and sends midi sysex messages on onsets,
so you can let a plugin react to it without writing the onset detection yourself.

b) devs can fork the project to get a nice starting point for a working onset detector.
please feel free to send pull requests if you make improvements! :)

BEWARE:

It was brought to my attention that the license is not permissive enough yet.
That is because I'm presenting the algorithm as part of a JUCE project here.
I'll change that soon to make it clear that the algorithm is supposed to work independently of JUCE
and because of that does not require the GPL license the full JUCE project is limited to.
