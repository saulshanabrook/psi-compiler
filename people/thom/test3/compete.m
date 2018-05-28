# compete.m is an implementation of a competitive learning neural network.
#  The network requires three procedures.  RESET resets the weights to
#  random values.  RUN loads input vectors from a file and runs them with
#  network and prints the output.  LEARN reads the input vectors from a file
#  computes the output of the network and adjusts the weights of the winner.
#  A set of vectors is learned by calling LEARN serveral times with the input
#  data and RUN can be used to show the results.

# reset initializes the weight array with nomalized random weights

reset(int n_in, int n_out, array A^2 <n_out n_in>)

{
  array i^1 <2>;
  array r^2 <1 1>;

  # initialize the weight vectors with zero or one
  for (<0 0> <= i < <n_out n_in>) {
    get_random(r);
    i pdrop A = r;
  }
  
  # normalize the weight vectors (rows of A)
  A=A / omega <1 0> (+red omega <1> A);
}


# run computes the output of the network for n_i inputs

run(int n_i, int n_in, int n_out, array A^2 <n_out n_in>)

{
  array input^1 <n_in>;
  array output^1 <n_out>;
  array win^1 <1>;
  array i^1 <1>;

  for (<0> <= i < <n_i>) {
    read_input(input);
 
    # compute the matrix vector product of A and norm(input)
    output=+red omega <1> ((input/(+red input)) * omega <1 1> A);

    # find the winner and make output binary
    winner(output,win);
    write_output(output);
  }
}


# learn is the same as run but updates the weights as the inputs is
# read to "learn" the inputs

learn(int n_i, int n_in, int n_out, array A^2 <n_out n_in>, array eta^0 <>)

{
  array input^1 <n_in>;
  array norm^1 <n_in>;
  array output^1 <n_out>;
  array win^1 <1>;
  array win2^1 <2>;
  array i^1 <1>;

  for (<0> <= i < <n_i>) {
    read_input(input);
    norm=input/(+red input);

    # compute the matrix vector product of A and norm(input)
    output=+red omega <1> (norm * omega <1 1> A);

    # find the winner and make output binary
    winner(output,win);

    # update the winners weight vector
    win2=win cat <0>;
    win2 pdrop A =(win psi A)+(eta*(norm-(win psi A)));
  }
}
