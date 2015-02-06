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
 * other binaries from pint also have to be in the PATH in order for their functionnalities to be available in gPH

##Compiler sur MacOS 
 * Ajouter ```QMAKE_CXXFLAGS += -stdlib=libc++``` dans .pro
 * Dans le clang_64/mkspecs/macx-clang/qmake.conf
   changer ```QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7(ou 10.6/10.8) ```
   à ```QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9 ```
 * Télécharger boost et graphviz dans /usr/local et changer des paths des bibliothèque dans .pro
 ** sur mon Mac, il faut bien préciser des paths des bibliothèques
 ** ```LIBS 		=  /usr/local/lib/boost/libboost_filesystem.a```
 ** ajouter des paths des fichiers sources de boost et graphviz 
   ```INCLUDEPATH += /usr/local/include/boost ```
   ```INCLUDEPATH += /usr/local/include/graphviz ```
 * S'il compile pas(avec des erreurs de boost), essayer de les retélécharger avec Homebrew
 ** ```brew boost```
 ** ```brew graphviz```
 ** aussi préciser des paths
 ** ```LIBS 		=  /usr/local/Cellar/boost/1.57.0/lib/libboost_filesystem.a```
 ** aussi ajouter des paths des fichiers sources de boost et graphviz 
   ```INCLUDEPATH += /usr/local/Cellar/graphviz/2.38.0/include/ ```
   ```INCLUDEPATH += /usr/local/Cellar/boost/1.57.0/include/ ```
 * Pour la question ```dyld: Library not loaded ```
 ** essayer ```brew install libtool --universal```  
            ```brew link libtool``` 
