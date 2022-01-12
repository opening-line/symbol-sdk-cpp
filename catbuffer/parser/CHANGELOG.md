# Changelog
All notable changes to this project will be documented in this file.

The changelog format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [3.1.0] - 22-Dec-2021

### Added
- struct attribute: implicit_size
- struct field sizeof directive

### Changed
- struct discriminator attribute supports multiple values

## [3.0.2] - 17-Dec-2021

### Added
- struct attributes: {size, initializes, discriminator}
- struct field attributes: {is_byte_constrained, alignment, sort_key}
- struct "abstract" modifier
- AST object model
- CATS DSL documentation

### Changed
- rewrite entire parser using Lark grammar
- array(...) syntax
- deprecated YAML output format

## [2.0.2] - 15-Sep-2021

### Fixed
 - actually generate proper YAML files

### Removed
 - one pass code generation

## [2.0.1] - 06-Sep-2021

### Added
 - YAML export option
 - 'inline struct' directive to express macro-like expansion
 - conditional support for array types

### Changed
 - enforce strict pythonic naming
 - parser output to YAML instead of python objects

## [2.0.0] - 02-Sep-2021

### Added
 - first class support for reserved fields with 'make_reserved' keyword
 - allow enum value names to be used as constant values
 - add 'not' keyword and support for negative conditions
 - allow numeric conditionals as well as enum conditionals
 - add support for numeric arrays

### Changed
 - replace `const` keyword with `make_const` to preserve a unified left to right flow
 - rename keyword 'has' to 'in'
 - deprecate explicit use of 'byte' type

## [1.0.0] - 19-Apr-2021

### Added
 - initial code release

[3.1.0]: https://github.com/symbol/catbuffer-parser/compare/v3.0.2...v3.1.0
[3.0.2]: https://github.com/symbol/catbuffer-parser/compare/v2.0.2...v3.0.2
[2.0.2]: https://github.com/symbol/catbuffer-parser/compare/v2.0.1...v2.0.2
[2.0.1]: https://github.com/symbol/catbuffer-parser/compare/v2.0.0...v2.0.1
[2.0.0]: https://github.com/symbol/catbuffer-parser/compare/v1.0.0...v2.0.0
[1.0.0]: https://github.com/symbol/catbuffer-parser/releases/tag/v1.0.0