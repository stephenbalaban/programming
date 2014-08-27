;; Implementing some of the macros from Chapter 7 of On Lisp.
(require '[clojure.string :as string])

(defn intersperse [sep list]
     (interpose sep list))

(defn psent [ & vals ]
  (println (str (string/capitalize (apply str vals))
                ".")))

;; p. 214
;; Need to generate a symbol for args.
(defmacro abbrev [short long]
  `(defmacro ~short [ & args# ]
     `(~'~long ~@args#)))


(defmacro defmacroprint [ name args & body ]
  `(do
     (psent "expanding macro " '~name " with args " '~args)
     (defmacro ~name ~args
        (do
          (psent "evaluating macro " '~name " with arg values: "
                 ~@(intersperse ", " (filter (fn [symb] (not= '& symb)) args)))
          ~@body))))

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


(defn start-tag [name]
  (str "<" name ">"))

(defn end-tag [name]
  (str "</" name ">"))

(dmp deftag [tag]
  `(defn ~tag [ & res#]
     (apply str
        (cons (start-tag '~tag) res#))))

(deftag html)
(deftag head)
(deftag title)
(deftag body)
(deftag h1)
(deftag h2)
(deftag p)

(let [doc (html
            (head
              (title "Hello"))
            (body
              (h1 "Hello World!")
              (p "This is a test of our html system")
              (h2 "This is a Header 2")
              (p "This is the last paragraph")))
      doc2 (p "HI")]
  (println doc))

(println (macroexpand '(deftag html)))
