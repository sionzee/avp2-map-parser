 # AVP2 Map .DAT Parser
Is a tool what can parse .DAT exported by DEdit for **Aliens vs Predator 2**.

### Note: This project is not finished yet. [WIP]

## Usage
1. **Download** the [latest release](https://github.com/sionzeecz/avp2-map-parser/releases) or **Clone** the project to your own machine
2. **Include** "core/Processor.h" to your project
3. **Call** *Processor::process(path_to_dat_file)* (returns pointer to Map struct) 
4. **Visit** *src/api/Map.h* and check for API calls :)

## Tests

To open tests map in DEdit you have to:
1. **UNREZ** AVP2 *unrez.bat is available from tool kit*
2. **Copy** cres.DLL, cshell.DLL, object.LTO and sres.DLL files to test/maps
3. **Copy** Attributes/ directory to test/maps
4. **Run** DEdit and you should be able to open **maps.dep**


## Issues
Feel free to submit issues and enhancement requests.

## Contributing
1. **Fork** the repo on github
2. **Clone** the project to your own machine
3. **Commit** changes to your own branch
4. **Push** your work back up to your fork
5. **Submit** a Pull request so that we can review your changes

>NOTE: Be sure to merge the latest from "upstream" before making a pull request!

