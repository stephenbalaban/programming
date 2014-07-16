(ns ch1.numbers)

(defn ll [n]
  "convert a float to our data structure"
  (str n))

(defn cmpchr [thing a b]
  "(cmpchr '> 1 3) => false"
  ((eval thing) (int a) (int b)))

(defn _gle [n1 n2]
  "a rule for comparing real numbers - TAoCP-1.2.2 #5"
  (let [m (first n1) 
        n (first n2)]
    (cond (and (nil? m) (nil? n)) '=
      (cmpchr '> m n) '>
      (cmpchr '< m n) '<
      :else   (_gle (rest n1) (rest n2)))))

(defn mkreal [n1]
  (clojure.string/split (str n1) #"\."))

(defn nnum [n]
  (read-string (first n)))

(defn ndec [n]
  (first (rest n)))

(defn gle [n1 n2]
  (let [nm (mkreal n1)
        nn (mkreal n2)
        m (nnum nm)
        n (nnum nn)]
    (cond (> m n) '>
          (< m n) '<
          :else   (_gle (ndec nm) (ndec nn)))))

(defn testthis [ex]
  (do (print ex "=> ")
      (print (str (eval ex)) "\n")))

(testthis '(gle 3.12930128391203 12903890123809123))
(testthis '(gle 3.1023 3.1023))
(testthis '(gle 3.333 3.332))
(testthis '(gle 1000 9.9999))
