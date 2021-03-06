/*

Copyright (c) 1993 Scott Thibault
All rights reserved.

THIS SOFTWARE IS PROVIDED BY THE DEVELOPER ``AS IS'' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED.  IN NO EVENT SHALL THE DEVELOPER BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
SUCH DAMAGE.

  poly.h - Type definitions for symbolic polynomials.

  4/93	- Scott Thibault
*/

/* poly_t - An array representation of a symbolic polynomial */

typedef struct {
  int  d;         /* the dimension of the polynomial (=number of variables) */
  int *shp;	  /* the shape of each dimension (shp[i] is the highest 
			degree of the variable represented by dimension i) */
  double *rav;     /* the contents of the array (=coefecients) */
}  poly_t;
