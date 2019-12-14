# AVP2 Map .DAT Parser
This this tool can extract content from .DAT file which is compiled by DEdit

## Usage
- Add AVP2MapReaderLib to your project
- Include ``core/Processor.h``
- Call ``Processor::process(path_to_dat_file)`` (returns pointer to Map struct)
- Visit ``api/Map.h`` and check for API calls :)

