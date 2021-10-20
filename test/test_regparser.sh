#!/bin/bash

diff <(cat <<EOF
 START
the DET
child NOUN
runs VERB
quickly ADV
to PREP
the DET
large ADJ
house NOUN
. END
EOF
) <(./regparser "the child runs quickly to the large house." | sed -E 's/ +/ /g;s/ $//g')

exit 0