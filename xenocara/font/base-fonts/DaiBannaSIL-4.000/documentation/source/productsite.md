---
title: Dai Banna SIL - Product Site
fontversion: 4.000
---

# Dai Banna SIL

![Dai Banna SIL - Banner](assets/images/dbsil_banner.png){.fullsize}
<!-- PRODUCT SITE IMAGE SRC https://software.sil.org/wp/wp-content/uploads/2022/07/dbsil_banner.png -->
<!-- <figcaption>Dai Banna SIL</figcaption> -->

<h2 id="about">About</h2>

Dai Banna SIL is a Unicode font package for rendering New Tai Lue (Xishuangbanna Dai) characters. It includes a complete set of New Tai Lue consonants, vowels, tones, and digits, along with punctuation and other useful symbols. Apart from a few New Tai Lue characters and Chinese punctuation marks, the design is the same as its predecessor, SIL Dai Banna (obsolete).

For a different style of New Tai Lue script, see SIL’s [Nokyung](https://software.sil.org/nokyung) fonts.

The New Tai Lue script is used by approximately 300,000 people who speak the Xishuangbanna Dai language in Yunnan, China. It is a simplification of the Tai Tham (Old Tai Lue) script as used for this language for hundreds of years.

We particularly thank the Dai News Department of Xishuangbanna Daily for valuable advice during the development of this Unicode font package. Xishuangbanna Daily, established in 1957, is the largest newspaper company in Yunnan, China that publishes in the New Tai Lue script.

## Linebreaking Control

The Dai Banna SIL fonts have built-in Graphite smart font code to control line breaking by allowing it between syllables only. This is useful because intersyllabic space is optional in New Tai Lue text, and without space marking syllable boundaries, standard applications will just break the line whenever it is full, likely splitting up a syllable.

To correctly render a run of text with no intersyllabic space, you must be using applications and/or operating systems that provide an adequate level of support for Graphite. Tested applications which make use of the Graphite capabilities of the fonts include:

- LibreOffice Writer (cross-platform)
- GrInD (for use with InDesign)

Non-tested but possible functionality might include these applications:

- FireFox browser
- XeTeX typesetting program

More information on Graphite technology and related applications is available at [Graphite](https://graphite.sil.org/).

<h2 id="downloads">Downloads</h2>

### License

These fonts are licensed under the [SIL Open Font License (OFL)](https://scripts.sil.org/OFL)

![SIL Open Font License (OFL)](assets/images/OFL_logo_rect_color.png){.fullsize}
<!-- PRODUCT SITE IMAGE SRC https://software.sil.org/wp/wp-content/uploads/2019/03/OFL_logo_rect_color.png -->

### Current Version

[sil_download style="table" sort="name" where="info.type == 'font'"]

### Release Notes for v4.000

The previous weights in two families (Dai Banna SIL Light and Dai Banna SIL Book) are now included in one family (Dai Banna SIL) with an additional weight (Medium).

For the New Tai Lue (Xishuangbanna Dai) characters the weights should be the same as before, just with different font names.
For example, Dai Banna SIL Light (Bold) is now Dai Banna SIL (SemiBold). Note the change in the font name and the (weight).

If there are any differences, the change in build tools (and sources) would probably be the reason.
The build process for the fonts completely changed to using open sources built using open source tools.

Most of the Latin characters have been replaced. In the previous release the Latin characters were the same weight
even if the New Tai Lue (Xishuangbanna Dai) characters were a different weight.
Now a different Latin font was imported (Gentium Plus) at the correct weight (such as Bold) and style (such as Italic).

### Previous Versions

[sil_download style="table" sort="-date" where="info.type == 'prev font'"]

[top]

## Information for Contributors

We welcome contributions to this font project, such as new glyphs, enhanced smart font code, or bug fixes. The best way to begin the process is to file an issue in the [Github Dai Banna SIL project](https://github.com/silnrsi/font-daibannasil) or respond to an existing issue and express your interest. Then we can begin to correspond with you regarding what all might be required and discuss how to best submit your contributions.

To enable us to accept contributions in a way that honors your contribution and respects your copyright while preserving long-term flexibility for open source licensing, you would also need to agree to the SIL International Contributor License Agreement for Font Software (v1.0) prior to sending us your contribution. To read more about this requirement and find out how to submit the required form, please visit the [CLA information page](https://software.sil.org/fontcla).

[top]

<h2 id="support">Support</h2>

As these fonts and utilities are distributed at no cost, we are unable to provide a commercial level of personal technical support. We will, however, try to resolve problems that are reported to us.

Before requesting technical support, please **carefully read all the documentation included with the fonts**. It can be found in the documentation folder.

[top]

<h2 id="contact">Contact</h2>

General troubleshooting information, including frequently asked questions, can be found in the documentation. Additional information is also available on the general [Font Help Guides](https://software.sil.org/fonts/guides/) pages.

### Language Software Community

[prodSupport lscpath='c/silfonts']

If that fails to answer your question, or you have a bug report, feature suggestion, or need help using the software, please contact us using the form below.

[contact-form-7 id="408" title="WSTech Products Contact Form"]

[top]
