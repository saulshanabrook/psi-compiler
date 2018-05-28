From lenore@cs.umr.edu Thu Oct 27 17:58 CDT 1994
Received: from sun7.cs.umr.edu (sun7 [131.151.6.57]) via ESMTP by sunserver.cs.umr.edu (8.6.9/D.3.00) id RAA02182; Thu, 27 Oct 1994 17:58:40 -0500
Received: from (lenore@localhost) by sun7.cs.umr.edu (8.6.9/M.3.00) id RAA14809; Thu, 27 Oct 1994 17:58:38 -0500
From: "Dr. Lenore Mullin" <lenore@cs.umr.edu>
Date: Thu, 27 Oct 1994 17:58:38 -0500
Message-Id: <199410272258.RAA14809@sun7.cs.umr.edu>
Apparently-To: tmcmahon@cs.umr.edu
Content-Type: text
Content-Length: 489
Status: O

main()
{
 array i^1 <1>;
# array j^0 <>;
 array y^2 < 5 6 >;
# const array llim^1 <1> = <1>;
# const array ulim^1 <1> = <3>;
 const array x^2 <6 6> = < 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18
                           19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34
                           35>;

 const array l^1 <1> = <1>;
 const array u^1 <1> = <3>;
# const array sigma^1 <1> = <0>;
 array j^0 <>;
 for( l <= i < u ){
    j = <0> psi i;
    y = <5> ptake omega <1 j> x;
 }
}


