---
title: Dai Banna SIL - Frequently Asked Questions
fontversion: 4.000
---

### Problems with Bold weights

For more details on the issue with Bold weights see [Using Axis-Based Font Families](https://software.sil.org/fonts/axis-based-fonts/).

#### *Why does my application not show the Bold weight in font menus and dialogs?*

Some applications will list all the weights but leave out Bold. To access the Bold you need to choose Regular and turn on Bold using the application's UI controls such as a "B" button.

#### *Why do I sometimes get a fake Bold?*

If you choose a weight other than Regular (such as Light), then use application controls to turn on Bold, some applications will make a "fake" Bold rather than use one of the real ones in the font (Medium, SemiBold, Bold). This is because only Regular has an associated Bold counterpart. This is a technical limitation with some apps and OSes. If you are using some other weight than Regular for text and want to make a word or phrase stand out you will need to select the text and apply one of the heavier weights manually.

### *Font linking: CJK punctuation rendered in other fonts - Windows*

Although the Dai Banna SIL fonts contain glyphs for some characters in the CJK Symbols and Punctuation block and the Halfwidth and Fullwidth Forms block, certain applications/operating systems will automatically choose a default Asian text font to display these characters instead.  This can usually be overridden by highlighting the whole run of New Tai Lue text and changing the font to one in the Dai Banna SIL family, but the following applications insist in font linking:

- Microsoft Word 2010 on Windows 7 Ultimate
- Microsoft Word 2016 on Windows 10

This is *not* a defect of our fonts but rather a failure of the applications/OS to recognise Dai Banna SIL as containing Asian (CJK) glyphs.

### *Misc.: Autofit row height gives initial blank line - Excel*

In a cell containing New Tai Lue text wrapped into multiple lines, the autofit function in Microsoft Excel (tested with Excel 2010 and 2016) may fail to compute the correct row height when the column width falls in a certain range. The result is that a blank line is left before the first line of text. This faulty behaviour is not a defect of our fonts but a bug of the application. Manual height adjustment can remove the blank line.
