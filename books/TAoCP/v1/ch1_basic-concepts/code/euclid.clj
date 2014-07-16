(ns ch1.euclid)

(defn mrem [m n]
  (if (< m n) m
      (mrem (- m n) n)))

(defn euclid [m n]
  (let [r (mrem m n)]
    (if (zero? r) n
        (euclid n r))))

(defn euclid-2 [m n]
  (if (zero? (mrem m n)) n
      (euclid (n (mrem m n)))))

(print "GCD(5,30) = " (euclid 5 30) "\n")
(print "GCD(100,29) = " (euclid 100 29) "\n")
(print "GCD(2,3) = " (euclid 2 3) "\n")
(print "GCD(25,100) = " (euclid 25 100) "\n")
(print "GCD(123,33) = " (euclid 123 33) "\n")
(print "GCD(2166,6099) = " (euclid 2166 6099) "\n")
(print "GCD(6099,2166) = " (euclid 6099 2166) "\n")
