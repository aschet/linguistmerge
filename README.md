# LinguistMerge

![Screenshot: A Merge Utility for Qt Localization TS Files](https://raw.githubusercontent.com/aschet/linguistmerge/main/screenshot.png)

Merging Qt localization TS files from multiple feature or release branches or reintegrating a delivery of a translation agency into the active development cycle can be quite challenging. LinguistMerge tries to ease this task. Think of it as a simplified lconvert with UI and the ability to combine duplicated messages. In the beginning this project startet out as a redesign of the [Merge-Qt-TS-files](https://github.com/savolai/Merge-Qt-TS-files) application but is now fully rewritten from scratch.

## Usage

- Load one or multiple TS files via **Add** or drag and drop TS files into the list view. 
- Click **Merge** to generate the merged TS file.

## Compiling from Source

A recent Qt 5 or Qt 6 is the only external dependency. Either open and build this project in Qt Creator via the Qt SDK or install the platform specific packages.

### Microsoft Windows

Setup the environment, open the Visual Studio command prompt and execute:

```
qmake
nmake
```

### Linux

Open the command prompt and execute:

```
qmake
make
```
