---
title: Dai Banna SIL - Developer Information
fontversion: 4.000
---

## Welcome font developers!

We welcome other developers who wish to get involved in supporting and enhancing these fonts or who want to modify them.

## Permissions granted by the OFL

SIL’s fonts are licensed according to the terms of the [SIL Open Font License](https://scripts.sil.org/OFL). The OFL allows the fonts to be used, studied, modified and redistributed freely as long as they are not sold by themselves. For details see the OFL.txt and OFL-FAQ.txt files in the package.

## Building the fonts from source code

The full source code for the Dai Banna SIL font is available on [Github](https://github.com/silnrsi/font-daibannasil)

Font sources are in the [UFO3](http://unifiedfontobject.org/versions/ufo3/) format with font family structures defined using [designspace](https://github.com/fonttools/fonttools/tree/master/Doc/source/designspaceLib).

The fonts are built using a completely free and open source workflow using industry-standard tools ([fonttools](https://github.com/fonttools/fonttools)), a package of custom python scripts ([pysilfont](https://github.com/silnrsi/pysilfont)), and a build and packaging system ([Smith](https://github.com/silnrsi/smith)). The whole system is available in a preconfigured virtual machine using VirtualBox and Vagrant.

Full instructions for setting up the tools and building SIL fonts are available on a dedicated web site: [SIL Font Development Notes](https://silnrsi.github.io/silfontdev/).

For building variable fonts (at this time, an experimental format for SIL fonts) run (on Linux and macOS; Windows requires slightly different commands):

- python3 -m venv variable
- source variable/bin/activate
- pip3 install gftools
- fontmake -m source/DaiBannaSIL-VF.designspace -o variable

The output will be in the `variable_ttf` directory.

## Contributing to the project

We warmly welcome contributions to the fonts, such as new glyphs, enhanced smart font code, or bug fixes. The [brief overview of contributing changes](https://silnrsi.github.io/silfontdev/en-US/Contributing_Changes.html) is a good place to begin. The next step is to contact us by responding to an existing issue or creating an issue in the Github repository and expressing your interest. We can then work together to plan and integrate your contributions.

Because we want to be able to guarantee a high level of quality for our fonts, we will review submissions carefully. Contributions will need to cover all the weights and styles of the family. Please don’t be discouraged if we do not include a submission due to quality or incompleteness, or if we ask you to make specific revisions.

To enable us to accept contributions in a way that honors your contribution and respects your copyright while preserving long-term flexibility for open source licensing, you would also need to agree to the **SIL International Contributor License Agreement for Font Software (v1.0)** prior to sending us your contribution. To read more about this requirement and find out how to submit the required form, please visit the [CLA information page](https://software.sil.org/fontcla).
