# dev (development)

This is a repo to jump start arbitrary development, mainly in C++, CMake,
Shell, but also Python, perhaps others to come.

It contains slots for pure temporaries (clean sheet, playground-like),
but also experimental stuff or examples that are meant to stay
for later reference.

It also serves as a place to develop foundational libs like utils that
are then included as submodules.

Testing 3rd-party libs is another use-case.

In general the list can be continued for sure, you shall really view the
repo as a clean sheet for any kind of sketch, draft, study.

## But it has grown a bit, where do I start?

* Almost always: `apps/tmp-cleansheet`
* `apps/tmp` is more loaded with (3rd-party) libs, not a completely green field.

## I like to conserve something for longer, where do I put it?

* `experiments` everything that is meant to be work in progress for longer
* `examples` 'finished' stuff that wants to be conserved
* `sdks` are the place for libs shared among various apps (obviously
beyond this repo), typically submodules for frequent development
* `3rdparty` the place for the obvious, might be archives or CMake scripts
(FetchContent, FindPackage, whatever). Of course, you should consider
not to push huge stuff into the repo that isn't appropriate to stay.

Obviously we have the distinction between `apps` and `libs`.
The local `util` lib is meant to provide utils only for this dev repo
exclusively.