Microwave Research Changelog
===============================

All notable changes to this project will be documented in this file.

The format is based on *[Keep a Changelog](https://keepachangelog.com/en/1.0.0/)*,
and this project adheres to *[Semantic Versioning](https://semver.org/spec/v2.0.0.html)*.

## [Unreleased]

## [1.0.1] - 2023-10-09
### Added
- Read/write imaging domain files added, defined in ImagingDomain.h
- Clock time measured in main
- Various comments and re-arranging to simplify main.c for readability
- Number of points in imaging domain is hand-calculated and defined in config.h as IMAGING_DOMAIN_POINTS

### Changed
- Memory de-allocation moved out of main to cleanup function defined in CSVReader.h
- All instances of MAX_POINTS changed to IMAGING_DOMAIN_POINTS, defined in config.h
- Variable name "index" in ImagingDomain.c changed to "idx"




## [1.0.0] - 2023-09-08
### Added
- Changelog

### Changed
- readIntArray, readDoubleArray, and readFloatArray simplified to use fixed array sizes defined in Config.h as number of channels, frequencies, and antenna locations respectively / 9-14-2023 - Colton
- Moved all file reading functions into a single function call to clean up main. Filenames are now defined in Config.h / 9-14-2023 - Colton

### Deprecated

### Removed

### Fixed

### Security