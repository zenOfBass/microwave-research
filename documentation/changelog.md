Microwave Research Changelog
===============================

All notable changes to this project will be documented in this file.

The formatting is based on *[Keep a Changelog](https://keepachangelog.com/en/1.0.0/)*,
and this project adheres to *[Semantic Versioning](https://semver.org/spec/v2.0.0.html)*.

## [Unreleased]
- Added Readme.md files, docs, and change log template / 2023-10-22 - Nathan
- Added Experiment struct / 2023-10-23 - Nathan
- Added Connection struct / 2023-10-24 - Nathan

## [1.1.0] - 2023-10-23
### Added
- SQL database
    - Function for writting to SQL
    - Class for complex data in SQL
    - Class for database
- User input for sweep parameters
- Error handling for user input and MegIQ/VNA connection
- Image subtraction
- Proportional permittivity in time delay

### Changed
- Moved sweeping, csv writing, and connetion processes into functions
- Cleaned up Sweep()
    - Split foreach loops in Sweep() into seperate functions
    - Switched i and j in nested loops and set them to start at 1
    - Loops based on sweep parameters
    - Switch() no longer static
- Cleaned up imaging files
    - Removed some arguments for csv reading functions
    - Moved variables to header files

### Removed
- Gcode support

## [1.0.1] - 2023-10-09
### Added
- Read/write imaging domain files added, defined in ImagingDomain.h
- Clock time measured in main
- Various comments and re-arranging to simplify main.c for readability
- Number of points in imaging domain is hand-calculated and defined in config.h as IMAGING_DOMAIN_POINTS
- Added -g flag in makefile for debugging

### Changed
- Memory de-allocation moved out of main to cleanup function defined in CSVReader.h
- All instances of MAX_POINTS changed to IMAGING_DOMAIN_POINTS, defined in config.h
- Variable name "index" in ImagingDomain.c changed to "idx"

### Removed
- Deleted unnecessary folders and data files

## [1.0.0] - 2023-09-16
### Added
- Changelog
- CloseMegiQ function

### Changed
- Brought sweeping and imaging into the same project
- readIntArray, readDoubleArray, and readFloatArray simplified to use fixed array sizes defined in Config.h as number of channels, frequencies, and antenna locations respectively / 2023-9-14 - Colton
- Moved all file reading functions into a single function call to clean up main. Filenames are now defined in Config.h / 2023-9-14 - Colton

### Removed
- Delay Multiply and Sum algorithm

### Fixed
- Imaging process
- Makefile's missing header files