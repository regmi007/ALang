ALang
==================
    Yet Another Programming Language.
    Features:
        - Object oriented.
        - Syntax similar to Python & SLang.

Build dependencies.
-------------------
    - flex: Lexical analysis.
      sudo aptitude install flex

    - bison: Parser genarator.
      sudo aptitude install bison

    - boost: Boost C++ library.
      sudo aptitude install libboost-dev

    - cmake: Build tool
      sudo aptitude install cmake

How to build.
-------------------
    - Inside /path/to/ALang
      $ cmake .
      $ make

How to run.
-------------------
    - Inside /path/to/ALang
      $ Src/ALang Example/Script.al

