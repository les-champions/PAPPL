# gPH
The Process Hitting is a recently introduced formalism suited for modelling qualitative dynamics of biological networks. It is a special class of Asynchronous Automata Networks.

**gPH** is a graphical interface for editing Process Hitting models.

[Pint](https://github.com/pauleve/pint/) implements the language, simulation, formal analysis, and translation of Process Hitting models.

![screenshot gPH](http://les-champions.github.io/gPH/images/gPH-screenshot-metazoan.png)

## Dependencies
### Compile-time
 * qt5
 * boost
 * graphviz

In ubuntu/debian, you can install these dependencies with
```
sudo apt install qt-sdk libgraphviz-dev libboost-filesystem-dev libboost-system-dev
```

### Run-time
 * phc, from [Pint](https://github.com/pauleve/pint/) is required to open files
 * other binaries from pint have to be in the PATH in order for their functionnalities to be available in gPH
