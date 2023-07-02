# C++20 Module Test

A very simple module experiment using C++20 and CMake based on this [MSVC Example](https://learn.microsoft.com/en-us/cpp/cpp/tutorial-named-modules-cpp?view=msvc-170)

# Build
- Build has only been tested for VS 2022

```
# Build and Generate CMake Files. Uses Visual Studio 2022
build.bat
# Can alternatively launch VS with the generated solution
```

# Module Overview

This example project uses MSVC naming conventions / setup. The "File Structure" descriptions are taken from this [MSVC Example](https://learn.microsoft.com/en-us/cpp/cpp/tutorial-named-modules-cpp?view=msvc-170#anatomy-of-a-module).

A module is generally composed of three types of files:
- Primary Module Interface (ModuleInterface.ixx)
- Module Partition (ModuleInterface-Partition.ixx)
- Module (Partiion) Implementation (ModuleInterface[-Partition].cpp)

## Primary Module Interface

The primary module interface file. Will import/export module partition and all other symbols that should be exported from the module. See `code/modules/BasicPlane.Figures.ixx` for an example.

File Structure:
```c++
module; // optional. Defines the beginning of the global module fragment

// #include directives go here but only apply to this file and
// aren't shared with other module implementation files.
// Macro definitions aren't visible outside this file, or to importers.
// import statements aren't allowed here. They go in the module preamble, below.

export module [module-name]; // Required. Marks the beginning of the module preamble

// import statements go here. They're available to all files that belong to the named module
// Put #includes in in the global module fragment, above

// After any import statements, the module purview begins here
// Put exported functions, types, and templates here

module :private; // optional. The start of the private module partition.

// Everything after this point is visible only within this file, and isn't 
// visible to any of the other files that belong to the named module.
```

## Module Partition

While not required, module partitions help organize code in a module. These are only meant to be imported within the module and should not be imported by other modules. See `code/modules/BasicPlane.Figures-Rectangle.ixx` and `code/modules/BasicPlane.Figures-Point.ixx` for an example.

```c++
module; // optional. Defines the beginning of the global module fragment

// This is where #include directives go. They only apply to this file and aren't shared
// with other module implementation files.
// Macro definitions aren't visible outside of this file or to importers
// import statements aren't allowed here. They go in the module preamble, below

export module [Module-name]:[Partition name]; // Required. Marks the beginning of the module preamble

// import statements go here. 
// To access declarations in another partition, import the partition. Only use the partition name, not the module name.
// For example, import :Point;
// #include directives don't go here. The recommended place is in the global module fragment, above

// export imports statements go here

// after import, export import statements, the module purview begins
// put exported functions, types, and templates for the partition here

module :private; // optional. Everything after this point is visible only within this file, and isn't 
                 // visible to any of the other files that belong to the named module.
```

## Module Implementation

Optional implementation file for modules. Implementation can be located in either the interface or the implementation file. Should implementation code be placed into the interface file, build times can possible increase when modifying the file since it will trigger a rebuild for all code that imports the module. Implementation files can avoid the rebuild when modifying code. 

```c++
// optional #include or import statements. These only apply to this file
// imports in the associated module's interface are automatically available to this file

module [module-name]; // required. Identifies which named module this implementation unit belongs to

// implementation
```
