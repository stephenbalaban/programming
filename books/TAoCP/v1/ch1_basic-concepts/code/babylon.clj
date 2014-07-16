(ns ch1.babylon)
"
From a Mathematician's lament.

x + y = a_v
x - y = b_v

x = b_v + y
y = a_v - x

b_v = x - (a_v - x)
    = x - a_v + x
    = 2x - a_v


a_v = x + y
    = b_v + 2y

y = (a_v - b_v) / 2
x = (b_v + a_v) / 2
"
(defn px [a b]
  (/ (+ a b) 2))

(defn py [a b]
  (/ (- a b) 2))

(defn dtest [x y a b]
  (let [r_x (px a b)
        r_y (py a b)]
    (do 
        (println "xResult: " (= x r_x) " Expected: " x " Got: " r_x)
        (println "yResult: " (= y r_y) " Expected: " y " Got: " r_y))))

(defn -main []
  (do 
      (dtest 200 100 300 100)
      (dtest 20 10 30 10)
      (dtest 2 10 12 -8)
      (dtest -2 -0 -2 -2)
      (dtest -2 10 8 -12)
  ))

(-main)
