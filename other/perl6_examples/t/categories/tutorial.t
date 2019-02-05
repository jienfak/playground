use v6;

use Test;

plan 1;

subtest {
    plan 1;

    my $name = "01-word-wrap";
    my $expected-output = q:to/EOT/;
Lorem ipsum dolor sit amet, consectetur adipiscing elit.
Suspendisse eu pharetra sapien. Nam rutrum condimentum nibh
a aliquam. Quisque placerat, est eget cursus feugiat, justo
magna mattis magna, at varius risus eros nec nisl. Praesent
nunc magna, viverra eget fermentum ut, ornare eget urna.
Aenean laoreet, nulla non dignissim mattis, sapien velit
volutpat velit, in condimentum lorem risus ut augue.
Curabitur quam leo, egestas id placerat et, luctus at nunc.
Phasellus eget orci enim, sit amet sagittis magna.
Suspendisse egestas enim ac sem aliquet lacinia. Quisque id
dui tortor. Aliquam libero augue, fermentum ut sollicitudin
sed, volutpat a enim. Cras gravida consectetur libero a
porttitor. Donec imperdiet sollicitudin gravida.

Etiam vehicula, ante vel venenatis luctus, nisi libero
vehicula tellus, nec aliquet est arcu nec metus. Nunc neque
lorem, ornare ac auctor id, sagittis id nisl. Integer
egestas imperdiet consequat. Nullam imperdiet scelerisque
purus quis convallis. Morbi porta rutrum magna, eget aliquet
libero sodales sed. Nunc eros arcu, cursus ac venenatis non,
tempor et neque. Nulla ac sem quis orci convallis eleifend
facilisis non purus. Morbi leo nulla, venenatis ullamcorper
condimentum vitae, feugiat id turpis. Mauris at sem mauris.
Etiam auctor ante non magna faucibus aliquam. Morbi ligula
eros, bibendum nec aliquam venenatis, dapibus sed erat. Nunc
vitae eros eros. Morbi sed velit nec libero suscipit congue.
In porttitor, augue non eleifend vulputate, tortor elit
faucibus quam, et rhoncus leo quam quis elit. Vestibulum
pretium, nunc sit amet mollis hendrerit, neque ligula
pharetra nisi, nec aliquam arcu nulla quis orci. Donec
imperdiet rutrum nisl eu sagittis. Pellentesque velit mi,
elementum sed pharetra a, tristique et lorem. Vivamus
facilisis, nibh eleifend bibendum tristique, purus ipsum
porta mauris, eget dignissim metus nibh vel est. Fusce
iaculis rutrum mi condimentum ultricies. Nunc laoreet
pulvinar pharetra.

In aliquet, odio tempus posuere tempus, felis arcu
consectetur lorem, in congue lectus massa sed nibh.
Curabitur feugiat rutrum sapien, sit amet venenatis nisl
placerat sit amet. Donec semper hendrerit nulla, id rhoncus
nunc eleifend ut. Phasellus quis odio id nisi egestas
euismod. Aliquam erat volutpat. Donec eros nulla, pharetra
vel aliquam ut, sagittis et eros. Nam velit quam, congue
eget ultrices sed, interdum tristique dolor. Morbi at leo
nec nulla volutpat viverra eget ut justo. Maecenas ultrices,
lectus in gravida mollis, erat arcu aliquet ipsum, quis
tincidunt arcu tortor ac diam. Pellentesque venenatis
molestie diam, eget varius ante sollicitudin nec. Phasellus
non sodales ligula. Fusce a velit in arcu feugiat hendrerit
id non erat. Proin fringilla placerat enim, vitae tincidunt
nunc luctus vitae. Nulla aliquet, erat in facilisis
placerat, enim nisi vulputate mauris, sodales feugiat neque
lectus id lectus. Nullam sodales, est id auctor lobortis,
lectus massa posuere tellus, commodo eleifend diam ligula
convallis arcu. Proin eros magna, sodales a aliquet ut,
eleifend at est.

EOT

    my $output = run-example($name);
    is($output, $expected-output, $name);

}, "01-word-wrap";


#| run the given example script
sub run-example($name) {
    my $base-dir = "categories/tutorial";
    my $script-path = $base-dir ~ "/" ~ $name;
    $script-path = "$script-path.pl".IO.e
    ?? "$script-path.pl"
    !! "$script-path.p6";
    my $base-cmd = "perl6 $script-path";
    my $output = qqx{$base-cmd};

    return $output;
}

# vim: expandtab shiftwidth=4 ft=perl6
