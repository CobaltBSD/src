---
title: Dai Banna SIL - Resources
fontversion: 4.000
---

## Requirements

These fonts are supported by all major operating systems (macOS, Windows, Linux-based, iOS, and Android), however the extent of that support depends on the individual OS and application.

## Installation

Install the fonts by decompressing the .zip archive and installing the fonts using the standard font installation process for .ttf (TrueType/OpenType) fonts for your platform. For additional tips see the help page on [Font installation](https://software.sil.org/fonts/installation).

## Keyboarding and character set support

These fonts do not include keyboards or other software for entering text. To type the symbols in these fonts use the keyboarding systems provided in your OS or use a separate utility. SIL’s [Keyman](https://keyman.com/) provides keyboards for over 2000 languages and works on all major desktop and mobile platforms. For information on other keyboarding options see the overview at [Keyboard Systems Overview (ScriptSource)](https://scriptsource.org/entry/ytr8g8n6sw).

See [Character set support](charset.md) for details of the Unicode characters supported by these fonts.

## Rendering and application support

In the previous version of the Dai Banna fonts (2.200), Graphite was needed to reorder four vowels to the left of the base consonant:

- U+19B5	ᦵ	NEW TAI LUE VOWEL SIGN E
- U+19B6	ᦶ	NEW TAI LUE VOWEL SIGN AE
- U+19B7	ᦷ	NEW TAI LUE VOWEL SIGN O
- U+19BA	ᦺ	NEW TAI LUE VOWEL SIGN AY

Before Unicode 8 these vowels were stored in logical order, i.e., consonants are always stored before vowels. In the previous version of the fonts, Graphite was needed to reorder these vowels so they display properly.

Now, these vowels are stored in visual order (i.e. before the consonant), so no reordering needs to be done in Graphite (or OpenType).

Graphite also allows smart line breaking that limits break opportunities to between syllables only.  This is useful because intersyllabic space is optional in New Tai Lue text, and without space marking syllable boundaries, standard applications will just break the line whenever it is full, likely splitting up a syllable, which is undesirable as per standard script usage.

To correctly render a run of text with no intersyllabic space, you must be using applications and/or operating systems that provide an adequate level of support for Graphite. Tested applications which make use of the Graphite capabilities of the fonts include:

- LibreOffice Writer (cross-platform)
- GrInD (for use with InDesign)

Non-tested but possible functionality might include these applications:

- FireFox browser
- XeTeX typesetting program

More information on [Graphite technology](https://graphite.sil.org/) and related applications is available.

The following script sample is taken from a traditional long poem.[^sample]  Notice how lines are broken depending on what application is being used:

　　　　ᦝᧂᦑᦸᦰᦵᦑᦲᧈᦓᦲᦰᦗᦻᦗᦲᧈᦈᧅᦶᦐᦏᦲᧈᦏᦾᧉᦟᧁᧈᦺᦞᧉᦺᦃᦂᦱᧇᦵᦂᧂᦆᧄᦂᦸᧃᧈᦵᦓᦲ，ᦅᧄᦙᦲᦺᦞᧉᦈᧅᦺᦃᦉᦱᧃᦍᦸᦍᦹᧃᧈ，ᦗᦸᦵᦖᦲᧃᦡᧂᧈᦶᦉᧃᦖᦹᧃᧈᦎᦳᧃᧉᦡᦸᧅᧈᦺᦙᧉᦺᦃᦂᦱᧇᦈᦸᧃᦟᦸᧃ，ᦎᦱᧄᦆᦱᧁᧈᦵᦙᦲᧂᦓᦅᦸᧃᦦᦱᧂᧉᦔᧃᦈᦱᦓᦅᦟᦱᧆ，ᦓᧅᦕᦱᧆᦈᧁᧉᦅᦳᧃᦣᦴᧉᦵᦙᦲᧈᦂᦸᧃᧈᦉᦸᧃᦔᧃ，ᦢᧁᧈᦺᦋᧈᦎᦱᦋᦻᦠᧃᦠᦱᧅᦒᧄᦟᧁᧈᦺᦞᧉ，ᦵᦟᧅᦋᦹᧈᦞᦱᧈᦵᦙᦲᧂᦺᦊᧈᦦᦱᧂᧉᦓᦅᦟᦱᧆᦔᧃᦈᦱᦞᦓᦱ，ᦠᦱᧅᦔᦲᧃᦵᦙᦲᧂᦷᦜᧂᦦᦱᧂᧉᦁᦱᦓᦱᦵᦣᦲᧂᦣᦳᧂᧈ，ᦑᦳᧂᧈᦓᦱᦦᦱᧂᧉᦟᦰᦟᧂᧉᦵᦟᧂᦟᦱᧇᦉᦂᧃᦎᦱ，ᦍᧂᦙᦲᦉᦱᦃᦱᦟᦸᧄᧉᦣᦲᧄᦵᦙᦲᧂᦡᦳᧂᦵᦏᦲᧃᧈ，ᦵᦟᦲᧃᧈᦟᦱᧃᧈᦓᧄᧉᦶᦙᧈᦦᦱᧂᧉᦺᦜᦕᦱᧈᦂᦱᧂᦵᦙᦲᧂ，ᦍᧂᦙᦲᦵᦟᦲᧂᦵᦗᦲᧂᦓᧄᧉᦐᦸᧂᦺᦉᦉᦜᦺᦊᧈ，ᦷᦌᧆᦌᦱᧆᦠᦸᧄᦡᦸᧅᧈᦺᦙᧉᦙᦸᧃᦍᦲᧂᧈᦈᦱᧄᦔᦱ，ᦁᧃᦞᦱᧈᦟᦤᦴᦠᦸᧂᧉᦔᦲᦵᦡᦲᧃᦉᦵᦖᦲᦵᦑᧂᧈ，ᦅᧃᦞᦱᧈᦏᦹᧂᦵᦃᧂᧈᦂᦱᧉᦍᦱᧄᦣᦸᧃᧉᦵᦙᧅᦆᦰᦜᧂᧈᦺᦜ，ᦃᦳᧂᦵᦙᦲᧂᦦᦱᧂᧉᦺᦉᦵᦟᦲᧂᦔᦲᧃᦋᦳᧄᧈ，ᦜᦻᦅᦱᧈᦚᦳᧂᦖᦱᧅᦉᦳᧄᧉᦟᦴᧅᦺᦙᧉᦢᧁᧈᦃᦱᧆᦔᦲᦵᦡᦲᧃ，ᦞᧃᦞᧃᦍᦲᧃᦵᦉᧂᦃᧇᦵᦉᦲᧃᦔᦲᧈᦶᦓᦙᦲᧈᦂᦸᧂᧉ，ᦙᦲᦑᧂᦵᦉᧂᦺᦠᧈᦅᦸᧂᧉᦵᦌᦲᧂ᧕ᦔᦲᧃᦅᦴᧈᦂᧇᦂᦸᧂ，ᦂᦱᧃᦃᦲᦖᦸᧂᦢᧁᧈᦙᦲᦙᦱᦺᦂᧉ，ᦺᦘᧈᦊᦴᧈᦑᦸᧂᧉᦵᦙᦲᧂᦦᦱᧂᧉᦜᦻᦖᦹᧃᧈᦜᧂᦵᦣᦲᧃ，ᦵᦖᦲᧃᦋᧂᧈᦵᦋᦲᧃ᧞ᦋᦱᧁᦊᦴᧈᦺᦓᦷᦆᧂᦝᦱᧉ，ᦚᦳᧂᦖᦴᧈᦙᦱᧉᦶᦟᧃᧈᦔᦾᧉᦶᦂᧄᦖᦴᧈᦷᦣᦩᦻ，ᦙᦲᦔᦲᧃᦷᦜᧂ᧞ᦜᦻ

[^sample]: Anonymous.  n.d.  《召树屯》.  n.p.  Reproduced in 《中国少数民族文字字符总集》, ed. Huang Xing et al.  Beijing: Institute of Ethnology & Anthropology, Chinese Academy of Social Sciences.  CD-Rom.

If the application does not support Graphite, the font will still work, although the line breaking will most likely not be as good as with Graphite.

## Web fonts

Web font versions of these fonts (in WOFF and WOFF2 formats) are available in the `web` folder. These can be copied to a web server and used as fonts on web pages. A very basic HTML/CSS demo page is also included. For more information on the options and techniques available for using these fonts on web pages see [Using SIL Fonts on Web Pages](http://software.sil.org/fonts/webfonts).

## Text conversion

These fonts are encoded according to [The Unicode Standard](http://unicode.org). If you have text that uses a legacy, non-Unicode encoding there are tools that can help you convert that text for use with Unicode fonts. See [Introduction to Text Conversion and Transliteration](https://scriptsource.org/entry/xlzd6n5aqt).
