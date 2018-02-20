=====
jessy
=====

``jessy`` is a kernel for *Intel® 64-bit* CPUs, written in modern C++ with
a minimal amount of assembler. The goal of ``jessy`` is to provide a safe and
efficient base for custom/experimental operating systems, leveraging the full
feature-set of the C++ programming language.

.. figure:: https://raw.githubusercontent.com/nfenclova/jessy/assets/images/screenshots/jessy_qemu_boot.png
   :alt: An early development screenshot
   :align: center

   An early development screenshot of ``jessy`` running in *QEMU*

Building
========

``jessy`` relies on modern C++ features (*ISO14882:2017* and later).
Development primarily happens in a Linux environment. This section
documents the software requirements and steps to build ``jessy``.

Requirements
------------

This section lists the software required to build ``jessy``, together with the
minimum (tested) version and packages for (tested) Linux distributions.

+----------------+-----------------+----------------------+
| Tool           | Minimum Version | Arch Linux Package   |
+================+=================+======================+
| GRUB 2         | 2.02            | core/grub            |
+----------------+-----------------+----------------------+
| CMake          | 3.10            | extra/cmake          |
+----------------+-----------------+----------------------+
| GCC x86_64-elf | 7.2.0           | aur/x86_64-elf-gcc   |
+----------------+-----------------+----------------------+
| QEMU           | 2.11.0          | extra/qemu           |
+----------------+-----------------+----------------------+
| Xorriso        | 1.4.8           | extra/libisoburn     |
+----------------+-----------------+----------------------+

Bootstrapping and Building
--------------------------

This section outlines the steps required to bootstrap a ``jessy`` development
and build environment, as well as how to get ``jessy`` running in *QEMU*.

Development Environment
~~~~~~~~~~~~~~~~~~~~~~~

1. Install the required software outlined above
2. ``git clone`` this repository:

   * read-only: ``git clone https://github.com/nfenclova/jessy``
   * read-write: ``git clone git@github.com:nfenclova/jessy``

Build Environment and First Boot
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. Open a shell
2. Change your working directory to the root of your clone. E.g.
   ``cd ~/git/jessy``
3. Bootstrap the build environment and perform the initial build:
   ``./support/tools/build.sh``
4. Change your working directory to the ``build`` folder in the root of your
   clone. E.g. ``cd build``
5. Start ``jessy`` in *QEMU*: ``cmake --build . --target boot``

Tools
=====

``jessy`` ships with some helper tools do make development easier. All of these
tools can be found ``support/tools/``. This section lists these tools and
describes their functionality.

+----------+-----------------------------------------------------------------+
| Tool     | Description                                                     |
+==========+=================================================================+
| build.sh | Build ``jessy``, bootstrapping the build environment if needed  |
+----------+-----------------------------------------------------------------+
| debug.sh | Start ``jessy`` in *QEMU*, attach *GDB* and break at ``_start`` |
+----------+-----------------------------------------------------------------+
| run.sh   | Start ``jessy`` in *QEMU*                                       |
+----------+-----------------------------------------------------------------+

``jessy`` also ships with a sourcable bash script that provides convenience
aliases for the tools mentioned above. The aliases are called:

* build
* debug
* run

each of which calling the respective tool.
