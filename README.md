Vertcoin Core integration/staging tree
=====================================

https://vertcoin.org

What is Vertcoin?
----------------

Vertcoin is a fork of Bitcoin that is designed to resist the monopolisation of
mining power.
 - 2.5 minute block targets
 - Subsidy halves in 840k blocks (~4 years)
 - 84 million total coins
 - 25 coins per block 
 - Difficulty retargeting every block to recover from large hashrate swings
 - Verthash proof of work algorithm for ASIC resistance

For more information, as well as an immediately useable, binary version of
the Vertcoin client software, see http://www.vertcoin.org.

License
-------

Vertcoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/vertcoin-project/vertcoin-core/tags) are created
regularly to indicate new official, stable release versions of Vertcoin Core.

Developers work on their own forks and submit pull requests in order to merge
changes with `master`. Due to the relatively small size of the development team,
developers also commit directly to the repo often. Anyone is allowed to contribute
though and useful pull requests will almost always be accepted given various
obvious stipulations regarding stability etc. 

The Vertcoin [discord](https://discord.gg/vertcoin) or [subreddit](https://reddit.com/r/vertcoin)
should be used to discuss complicated or controversial changes with the developers 
before working on a patch set.

Testing
-------

Vertcoin currently relies on Bitcoin Core for its testcases, and few of them are
known to work, though the software is based on fully tested conforming upstream 
Bitcoin Core versions. We would be grateful to those who can help port the existing
Bitcoin Core test cases to Vertcoin such that they can be used to assure correctness.

Translations
------------

Changes to translations as well as new translations can be submitted to as pull
requests to this repo or to upstream Bitcoin Core.
