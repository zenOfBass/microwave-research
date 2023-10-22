Microwave Research Changelog
===============================

All notable changes to this project will be documented in this file.

The format is based on *[Keep a Changelog](https://keepachangelog.com/en/1.0.0/)*,
and this project adheres to *[Semantic Versioning](https://semver.org/spec/v2.0.0.html)*.

## [Unreleased]

## [1.0.0] - 2023-09-16
### Added
- Changelog
- CloseMegiQ function

### Changed
- Brought sweeping and imaging into the same project

### Removed
- Delay Multiply and Sum algorithm

### Fixed
- Imaging process
- Makefile's missing header files

## [1.1.0] - 2023-10-10
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
- Broke sweeping, csv writing, and connetion processes into functions
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