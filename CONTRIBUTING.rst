=========================
Contributing to ``jessy``
=========================

``jessy`` is an open-source software project. Following in the spirit of
open-source, ``jessy`` and open to anyone willing to invest time into the
project, regardless of race, religion, or gender as well as political-,
religious-, or spiritual ideology. ``jessy`` is a project focused on providing
a modern, safe, and efficient operating system kernel for modern PCs and
virtual machine emulators.

All contributions, no matter who designed, implemented, or worked on them,
have to follow the guideline outlined below. Failing to do so might lead to
the contribution to be rejected or having acceptance postponed until the
issues are fixed.

Guidelines
==========

This section outlines the general guidelines that every contribution has to
follow. While exceptions to these guidelines might be possible, submissions in
violation of the guidelines can and will be rejected.

Code Style
----------

The code of ``jessy`` uses a variant of the *Whitesmith's* indentation style.
Unfortunately, there are currently no support files to aid with automatic
indentation checks, as well as no formal specification. Look at the code that
is present, and try to adhere to the same formatting for the time being.

Naming
------

The names of *visible* entities like functions, classes, constants,
namespace-scoped variable, and public members of class-types are to use
``snake_case``, unless specified otherwise.

Names of ``template<>`` Parameters are to use ``PacalCase``, unless specified
otherwise. [ Note --- This includes type-, non-type-, and
template-template parameters --- end note ]

All names have to be clear, obvious, and speak for themselves. Dnt lv t lttrs
jst fr th hck f t, and don't abbr. unn'y!

Commit Messages
---------------

The first line of a commit message has to be no longer than **50** characters.
It shall be written in **present-tense** and give a brief description of what
the change is designed to do. Prefix every commit message with the affected
part of the project, for example: ``vga: implement screen clearing``,
``doc: add documentation for multiboot_tag``, or ``build: enable optimization
selection``.

**If required**, provide a more detailed description **after** leaving a blank
line after the subject line. Don't explain, what you did, rather describe the
effect.
