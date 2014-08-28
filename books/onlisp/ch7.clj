;; Implementing some of the macros from Chapter 7 of On Lisp.
(require '[clojure.string :as string])
(use 'clojure.pprint)
(use 'clojure.walk)

(defn intersperse [sep list]
     (interpose sep list))

(defn printsnt [ & vals ]
  (println (str (string/capitalize (apply str vals))
                ".")))

;; p. 214
;; Need to generate a symbol for args.
(defmacro abbrev [short long]
  `(defmacro ~short [ & args# ]
     `(~'~long ~@args#)))

(abbrev dmp defmacroprint)

(defmacro macdbg [ expr ]
  `(pprint (macroexpand-all '~expr)))

(defmacro defmacroprint [ mname args & body ]
  `(do
     (printsnt "expanding macro " '~mname " with args " '~args)
     (let [macro# '(defmacro ~mname ~args
       (do (printsnt "evaluating macro " '~mname " with arg values: "
            ~@(intersperse ", " (filter (fn [symb] (not= '& symb)) args)))
           ~@body))]
       (eval macro#)
       ;(printsnt "This macro, " '~mname " will expand to the lisp code below")
       ;(pprint (macroexpand-all macro#))
       )))

;; easy currying macro + helper function.
(defn curry-up [fname params body]
  (if (empty? params)
      body
      (list 'fn [(first params)] (curry-up fname (rest params) body))))

(dmp defnc [ fname params body ]
  `(defn ~fname [~(first params)]
     ~(curry-up fname (rest params) body)))

(abbrev dmp defmacroprint)

;; p. 87
(dmp our-when [test & body]
    `(if ~test
         (do
           ~@body)))

(dmp another-macro [ & body ]
  `(do
      (println "inside blah")
      (reduce + body)))


(println "Here are some macros from On Lisp, in action!")
(our-when true
       (println "When was true!"))

;; Without currying.
(defn tag-n [start finish]
  (fn [tname]
    (str start tname finish)))

(defn start-tag-n [tname]
  (tag-n "<" ">"))

(defn end-tag-n [tname]
  (tag-n "</" ">"))

;; With currying.
(defnc tag [start finish tname]
       (str start tname finish))

(def start-tag ((tag "<") ">"))

(def end-tag ((tag "</") ">"))

(defn adder-c [n]
  (fn [a] (+ a n)))



(defnc adder [a n]
       (+ a n))

(defnc sumWith [summand others]
       (+ summand (reduce + others)))

(defnc abc [a b c d e f g]
  (+ a b c d e f g))
(macdbg (defnc abc [a b c d e f g]
  (+ a b c d e f g)))

;; need to add support for comments, kwargs, and multi-arity override!
(comment
  (defnc +
    "Returns the sum of nums. (+) returns 0. Does not auto-promote
      longs, will throw on overflow. See also: +'"
    {:inline (nary-inline 'add 'unchecked_add)
        :inline-arities >1?
        :added "1.2"}
    ([] 0)
    ([x] (cast Number x))
    ([x y] (. clojure.lang.Numbers (add x y)))))

(comment
(macdbg
(defnc +m
    "Returns the sum of nums. (+) returns 0. Does not auto-promote
      longs, will throw on overflow. See also: +'"
    {:inline (nary-inline 'add 'unchecked_add)
        :inline-arities >1?
        :added "1.2"}
    ([] 0)
    ([x] (cast Number x))
    ([x y] (. clojure.lang.Numbers (add x y))))))

;;(println (str "We need 10 +m 15 = " ((+m 10) 15)))

(macdbg (defnc sumWith [summand others]
       (+ summand (reduce + others))))

((comp println str) "sumWith 10 (range 1 101) should be equal to 5050 + 10 = 5060. In our case it equals: " ((sumWith 10) (range 1 101)))

(defnc idd [x]
       x)

(def add2 (idd (adder 2)))

(macdbg (defnc adder [a n] (+ a n)))

(println (str "Adder: " add2 " add2 + 10 = " (add2 10)))

(defmacro deftag [tag]
  `(defn ~tag [ & res#]
     (apply str
       (concat (list (start-tag '~tag))
               res#
               (list (end-tag '~tag))))))

(deftag html)
(deftag head)
(deftag title)
(deftag body)
(deftag div)
(deftag h1)
(deftag h2)
(deftag p)

(let [doc (html
            (head
              (title "Hello"))
            (body
              (h1 "Hello World!")
              (div (div (p "HI")
                        (h2 "OK")))
              (p "This is a test of our html system")
              (h2 "This is a Header 2")
              (p "This is the last paragraph")))
      doc2 (p "HI")]
  (println doc))

(macdbg (deftag html))

(comment

(defn abc [a]
  (->> a
       (for [i forms] id)
       (fn [x] x)))

(defn abc [a b c d e f g]
  (+ a b c d e f g))

(def abc-c
 (fn [a]
  (fn [b]
   (fn [c]
    (fn [d]
     (fn [e]
      (fn [f]
       (fn [g]
        (+ a b c d e f g)))))))))
    )
