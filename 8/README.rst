Steps to build and run the project
==================================

1. Create the "bin" folder and go to it

.. code:: sh
    mkdir bin & cd bin

2. Generate build files

.. code:: sh
    cmake .. -G "MinGW Makefiles"

3. Build the project

.. code:: sh
    cmake --build .

4. Run main file passing name of the file as a parameter

.. code:: sh
    main filename