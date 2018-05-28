main()
{
  array i^0 <>;
  array b5^2 <10 30>;
  array fish^2 <10 30>;

  b5 = (<5> drop fish) cat (<5> take fish);

  a4 = (<15> drop ((<15> drop fish) cat (<15> take fish))) cat
       (<15> take ((<15> drop fish) cat (<15> take fish)));

  fish = (<5> drop omega <1 1> b5) cat omega <1 1>
	 (<5> take omega <1 1> b5);
}
