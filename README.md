<div align="center">

# XML TO Yang Convertor

Accelerate your YANG model development process with XML to YANG Convertor - the lightning-fast and intuitive XML to YANG conversion tool. It's the ultimate conversion tool for simplifying network management.
 
•  [Features](#features)  • 
[Installation](#installation)  • 
[Configurations](#configurations)  • 
[Roadmap](#roadmap)  • 
[Acknowledgment](#acknowledgement)
 
</div>

## <div align="center">Features</div>
- [x] Fast conversion of XML schemas to YANG models.
- [x] Configurable module name, namespace, prefix, and revision.
- [x] Exporting YANG models to file.
- [x] Dynamically creates container, leaf, and list elements.
- [x] Automatically Extracts attributes and their values from XML files and creates YANG objects.
- [x] Adds description and key statements to container and list elements respectively dynamically.
- [x] 



## <div align="center">Installation</div>
#### <div>Requirements</div>
- A modern operating system (macOS, Windows, Linux, or ARM64)
- libxml2 and glib development packages installed
- A C compiler (e.g., GCC, Clang, or MSVC)

#### macOS

1. Install libxml2 and glib using Homebrew:

```bash
brew install libxml2 glib
```

2. Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/carolinestanly/xml_to_yang_convertor.git
cd xml_to_yang_convertor
```
#### Windows

1. Install MSYS2.

2. Open MSYS2 terminal and update the package database and base packages:
```bash
pacman -Syu
```

3. Close the terminal and reopen it.

4. Install required libraries:
 ```bash
pacman -S mingw-w64-x86_64-libxml2 mingw-w64-x86_64-glib2
```

5. Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/carolinestanly/xml_to_yang_convertor.git
cd xml_to_yang_convertor
```

### Linux and ARM64
1. Install libxml2 and glib development packages:
```bash
sudo apt-get install libxml2-dev libglib2.0-dev
```
2.Clone the repository and navigate to the project directory:
```bash
git clone https://github.com/carolinestanly/xml_to_yang_convertor.git
cd xml_to_yang_convertor
```

## <div align="center">Compilation</div>

To compile the project using the provided Makefile, run:
```bash
make clean
make
```
## <div align="center">Running the convertor</div>
Modify the input and output path. Execute the execute.sh script to run the convertor with the specified input XML file and output directory:
```bash
./execute.sh
```

## <div align="center">Configurations</div>
<table>
  <tr>
    <th>S.No</th>
    <th>Name</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>1</td>
    <td>name</td>
    <td>Module name of the YANG.Match the YANG module name with the file name to ensure consistency.</td>
  </tr>
 
  <tr>
    <td>2</td>
    <td>namespace</td>
    <td>An unique identifier for YANG modules.</td>
  </tr>
 <tr>
    <td>3</td>
    <td>prefix</td>
    <td>Short label to reference a YANG module's namespace.</td>
  </tr>
 <tr>
    <td>4</td>
    <td>revision</td>
    <td>The version number assigned to YANG modules to track changes made over time.</td>
  </tr>
</table>


## <div align="center">Roadmap</div>

- [ ] Improved error handling and reporting
- [ ] Grouping of the YANG nodes.
- [ ] Enable Dual XML Migration followed by YANG Conversion.
- [ ] Validates the output yang after conversion
- [ ] Compare XSD and XML to enable YANG conversion.


## <div align="center">Acknowledgement</div>

* [LibXML](https://gitlab.gnome.org/GNOME/libxml2)&nbsp;
* [GLIB](https://gitlab.gnome.org/GNOME/glib)&nbsp;
