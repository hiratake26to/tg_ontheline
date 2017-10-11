/**
 * license is free
 * \file    ontheline.cpp
 * \author  tfd36521@st.yamagata-u.ac.jp
 * \date    2017-10-11 JST
 */
#include <iostream>
#include <boost/numeric/ublas/vector.hpp>

/**
 * \brief mouse pointer is on the line
 * \param xa  x of equipment A
 * \param ya  y of equipment A
 * \param xb  x of equipment B
 * \param yb  y of equipment B
 * \param xc  x of mouse pointer
 * \param yc  y of mouse pointer
 * \param r   line width
 */
bool isOnTheLine(int xa, int ya, int xb, int yb, int xc, int yc, int r);

int main() {
  /*    0 1 2 3 4 
   * 0  _ _ _ _ _
   * 1  _ _ _ B _
   * 2  _ _ @ _ _
   * 3  _ @ _ _ _
   * 4  A _ _ _ _
   */
  bool result;
  result = isOnTheLine(0, 4, 3, 1, 2, 2, 1);
  std::cout << "result : " << result << std::endl;
  std::cout << "--------------------------" << std::endl;
  result = isOnTheLine(0, 4, 3, 1, 3, 2, 1);
  std::cout << "result : " << result << std::endl;
  std::cout << "--------------------------" << std::endl;
  result = isOnTheLine(0, 4, 3, 1, 4, 3, 1);
  std::cout << "result : " << result << std::endl;
  std::cout << "--------------------------" << std::endl;
  result = isOnTheLine(0, 4, 3, 1, 4, 0, 0);
  std::cout << "result : " << result << std::endl;
  return 0;
}

bool isOnTheLine(int xa, int ya, int xb, int yb, int xc, int yc, int r)
{
  namespace ublas = boost::numeric::ublas;

  // point C is mouse pointer
  // point X is point at the intersection of AB with CX
  // vector CX is perpendicular line from C to line AB
  ublas::vector<double> v_AB(2);
  ublas::vector<double> v_nAB(2); // nAB is unit vector of AB
  ublas::vector<double> v_AC(2);
  ublas::vector<double> v_AX(2);
  ublas::vector<double> v_CX(2);
  double len_AB;                  // length of vector AB
  double len_AX;                  // length of vector AX
  double len_CX;                  // length of vector CX

  // vector AB
  v_AB[0] = xb - xa; // AB.x
  v_AB[1] = yb - ya; // AB.y
  // length of AB
  len_AB = ublas::norm_2(v_AB);

  // unit vector nAB
  v_nAB = v_AB / len_AB;

  // vector AC
  v_AC[0] = xc - xa; // AC.x
  v_AC[1] = yc - ya; // AC.y

  // length of AX
  len_AX = ublas::inner_prod(v_AC, v_nAB); // (AC,nAB)
  // vector AX
  v_AX = v_nAB * len_AX; // AX = nAB*|AX|

  // vector CX
  v_CX = v_AX - v_AC;
  // length of CX
  len_CX = ublas::norm_2(v_CX);

  // debug log
  std::cout << "length of AB    : " << len_AB << std::endl;
  std::cout << "length of AX    : " << len_AX << std::endl;
  std::cout << "dist from C to X: " << len_CX << std::endl;
  std::cout << "check length CX : "
    << ((len_CX < r)?"true":"false") << std::endl;
  std::cout << "check length AX : "
    << ((len_AX < len_AB)?"true":"false") << std::endl;

  bool pointer_isOnLine = (len_CX < r) && (len_AX <= len_AB);

  return pointer_isOnLine;
}
