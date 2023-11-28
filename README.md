# Yeti
> Yeti es un Robot creado en el marco de los Juegos Bonaerenses de Robotica. Capaz de competir en las disciplinas de Sumo, Velocidad y Control y Despejar el Area.

[![NPM Version][npm-image]][npm-url]
[![Build Status][travis-image]][travis-url]
[![Downloads Stats][npm-downloads]][npm-url]


![](header.png)

## Modo Sumo

Se trata de un modo en el cual se coloca a dos robots en una pista circular(dohyo) en forma de oposicion. Estos se deben empujar, y el primero en caerse perdera. Gana el mejor de tres rondas. Cabe destacar que este es un modo controlado, distinto de los demas que son totalmente autonomos.


## Modo Velocidad y Control

Consiste de un seguidor de linea: Se posiciona el robot en una pista blanca delimitada con negro y tiene que completar ese circuito en el menor tiempo posible.

## Modo despejar el Área

Se coloca el robot en un area blanca cuadrada con limites negros en la cual hay ciertos obstaculos. El robot debe limpiar este área en el menor tiempo posible. Si llegase a salir de la pista seraá penalizado.  

## Release History

* 0.2.1
    * CHANGE: Update docs (module code remains unchanged)
* 0.2.0
    * CHANGE: Remove `setDefaultXYZ()`
    * ADD: Add `init()`
* 0.1.1
    * FIX: Crash when calling `baz()` (Thanks @GenerousContributorName!)
* 0.1.0
    * The first proper release
    * CHANGE: Rename `foo()` to `bar()`
* 0.0.1
    * Work in progress

## Meta

Your Name – [@YourTwitter](https://twitter.com/dbader_org) – YourEmail@example.com

Distributed under the XYZ license. See ``LICENSE`` for more information.

[https://github.com/yourname/github-link](https://github.com/dbader/)

## Contributing

1. Fork it (<https://github.com/yourname/yourproject/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

<!-- Markdown link & img dfn's -->
[npm-image]: https://img.shields.io/npm/v/datadog-metrics.svg?style=flat-square
[npm-url]: https://npmjs.org/package/datadog-metrics
[npm-downloads]: https://img.shields.io/npm/dm/datadog-metrics.svg?style=flat-square
[travis-image]: https://img.shields.io/travis/dbader/node-datadog-metrics/master.svg?style=flat-square
[travis-url]: https://travis-ci.org/dbader/node-datadog-metrics
[wiki]: https://github.com/yourname/yourproject/wiki
