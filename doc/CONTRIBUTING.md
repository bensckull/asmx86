# Guide de contribution au projet ASMx86

Ce guide présentera les différentes règles de normalisation de développement qui
seront utilisées dans l'optique de la réalisation de ce projet.

L'ensemble du code devra être réalisé en anglais (variables, fonctions, etc). La
documentation quand à elle pourra être écrite en français.

## Nom de classes

Les classes utiliseront la syntaxe **CamelCase**, qui implique l'utilisation de
majuscules et l'absence d'espaces.

```
class File {}

class ASMParser {}
```

## Nom de variables

Les variables utiliseront la syntaxe **underscore_case**, qui implique
l'utilisation d'underscore et d'éviter les casses majuscules.

```
const std::String full_path;
std::String base_name;
```

## Taille maximale des lignes

Une ligne de code ne devra pas dépasser les **100 caractères**.

## Indentations

L'indentation se fera à l'aide de **4 espaces**.

## Accolades

Les classes et fonctions utiliseront **un saut de ligne** avant la première
accolade afin de permettre une meilleure lisibilité.

Les conditions (if, while, etc) utiliseront **un espace** avant la première
accolade.

```
class File
{
    public:
        file(const std::String path)
        {
            if(path.size() == 0) {
                std::cerr << "Houston, there is a problem" << std::endl;
            }
        }
}
```

## Documentation

La documentation des classes et fonctions sera réalisée avec l'aide de
[doxygen](http://www.stack.nl/~dimitri/doxygen).

Un exemple est disponible
[à cette adresse](http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html).
