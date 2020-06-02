DESTDIR=${DESTDIR:-"/"}
PREFIX=${PREFIX:-"/usr"}
BINDIR=${BINDIR:-"$PREFIX/bin"}
DATADIR=${DATADIR:-"$PREFIX/share"}

install -vDm755 src/sys-{locale,usrgrp} -t $DESTDIR/$BINDIR/
install -vd $DESTDIR/$DATADIR/sys-mgr/usrgrp
cp data/share/usrgrp/* $DESTDIR/$DATADIR/sys-mgr/usrgrp