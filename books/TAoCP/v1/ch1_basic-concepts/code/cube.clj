(ns ch1.cube)

(defn cvol [n]
  (* n n n))

(defn pvol [n]
  "the volume of a regular, 4 sided pyramid with base n x n x n"
  (/ (* n n n) 3))

(defn remain [n]
  (- (cvol n) (pvol n)))

(defn testme [n]
  (str "Testing n: " n " pvol: " (pvol n) " cvol: " (cvol n) " ratio: " (/ (cvol n) (pvol n)) "\n"))

(defn -maizn []
   (for [n (range 1 30)] (str (testme n))))

(println (-maizn))

"
 --- 
| X | = infinite sum of area of decreasing squares
 ---

n * (n * n) / 2

  ^
. | .    1/2 b * h
-----

n * n / 2

We know that a pyramid that fits inside of a cube can be tesselated 
with 6 of itself to make a larger cubicthing of size:

2n * n * n

comprised of examptly 6 pyramids

2 * n^3     n^3
------- =  -----
   6         3

thus...

"
