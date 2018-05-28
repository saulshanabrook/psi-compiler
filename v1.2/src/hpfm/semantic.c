void subroutine_subprogram_s1 ()
{
  char buf[1024]; statement_t *body=NULL;
  line[0]=0;

  if ((tfile=fopen("temp$$$$.moa","wt"))==NULL) {
    fatal("Couldn't create temporary file.");
  }
  if ((vfile=fopen("vtemp$$$$.moa","wt"))==NULL) {
    fatal("Couldn't create temporary file.");
  }

  if (host) {
    if ((hfile=fopen("htemp$$$$.moa","wt"))==NULL)
      fatal("Couldn't create temporary file.");
  }
}

void subroutine_subprogram_s2 ()
{
  if (host) {
    fprintf(hostfile,"USE %s\n",arch_module);
    fprintf(hostfile,"USE MOALIB\n");
  }
  if (n_procs>1)
    fprintf(cfile,"USE %s\n",arch_module);
  fprintf(cfile,"USE MOALIB\n"); 
}

void subroutine_subprogram_s3 ()
{
  char buf[1024];

  declare_utils();
  fclose(tfile);
  fclose(vfile);
  if (host)  fclose(hfile);

  fprintf(cfile,"\n! MOA\n! Variable declarations\n!\n");
  if ((vfile=fopen("vtemp$$$$.moa","r"))==NULL) {
    fatal("Couldn't open temporary file.");
  }
  fgets(buf,1024,vfile);
  while (!feof(vfile)) {
    fputs(buf,cfile);
    fgets(buf,1024,vfile);
  }
  fclose(vfile);
  fputs("\n",cfile);

  if (n_procs>1) fprintf(cfile,"  call NODE_INIT()\n\n");

  if (host) {
    fprintf(hostfile,"\n  call HOST_INIT()\n\n");
  }

  if (host) {
    if ((hfile=fopen("htemp$$$$.moa","r"))==NULL) {
      fatal("Couldn't open temporary file.");
    }
    fgets(buf,1024,hfile);
    while (!feof(hfile)) {
      fputs(buf,hostfile);
      fgets(buf,1024,hfile);
    }
    fclose(hfile);
  }

  if ((tfile=fopen("temp$$$$.moa","r"))==NULL) {
    fatal("Couldn't open temporary file.");
  }
  fgets(buf,1024,tfile);
  while (!feof(tfile)) {
    fputs(buf,cfile);
    fgets(buf,1024,tfile);
  }
  fclose(tfile);
 
  free_tmp_mem();    /* free any temporary memory used */

}

void execution_part_s1 (statement_t *node)
{
  if (node != NULL) {
    while (node->next != NULL) node=node->next;
    node->next = NULL;
    code_c(body,partition(body));
  }
}

void constant_s1 (int val)
{
  sprintf(line+strlen(line),"%d",val);
}

void constant_s2 (double val)
{
  sprintf(line+strlen(line),"%f",val);
}

s_expr_t *s_constant_s1 (int neg, int val)
{
  s_expr_t *s;

  s=get_s_expr();
  s->ident=get_ident();
  s->ident->real=FALSE;
  s->ident->type=CONSTANT;
  s->ident->value=(double)val);
  if (neg) s->ident->value*=-1.0;
}

ident_t *type_spec_s1 (int real)
{
  ident_t *ret;

  ret = get_ident ();
  ret->type = VARIABLE;
  ret->real = real;
  if (real) {
    sprintf(line+strlen(line),"  REAL");
  } else {
    sprintf(line+strlen(line),"  INTEGER");
  }
}
