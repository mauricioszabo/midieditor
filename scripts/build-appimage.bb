(defn sh-or-die [ & args]
  (let [res (apply shell/sh args)]
    (when (not= 0 (:exit res))
      (throw (ex-info "Failed to run code" {:result res :code args})))
    res))

(defn get-dependencies []
  (->> (sh-or-die "ldd" "-v" "MidiEditor")
       :out
       str/split-lines
       (map #(second (re-find #".* => (.*)" %)))
       (filter identity)
       (map #(str/replace % #" \([\da-fx]+\)" ""))
       distinct))

(defn copy-dependencies-to-appimage []
  (shell/sh "mkdir" "-p" "AppDir/usr/bin")
  (sh-or-die "cp" "packaging/unix/midieditor/MidiEditor.desktop" "AppDir")
  (sh-or-die "cp" "packaging/unix/midieditor/logo48.png" "AppDir/midieditor.png")
  (sh-or-die "cp" "MidiEditor" "AppDir/usr/bin/midieditor")
  (shell/sh "rm" "AppDir/AppRun")
  (sh-or-die "ln" "-s" "./usr/bin/midieditor" "AppDir/AppRun")

  (let [deps (get-dependencies)
        dirs (->> deps
                  (map #(second (re-find #"(.+)/" %)))
                  distinct)
        dir-libs (->> dirs
                      (map #(str "$ORIGIN/../.." %))
                      (str/join ":"))]
    (println "Creating directories in AppImage root")
    (doseq [dir dirs]
      (println "Creating directory" (str "AppDir" dir))
      (shell/sh "mkdir" "-p" (str "AppDir" dir)))

    (println "Copying libs")
    (doseq [dep deps]
      (println "Copy" dep "to" (str "AppDir" dep))
      (sh-or-die "cp" dep (str "AppDir" dep))
      (sh-or-die "patchelf" "--set-rpath" dir-libs (str "AppDir" dep)))
    (sh-or-die "patchelf" "--set-rpath" dir-libs "AppDir/usr/bin/midieditor")))

(copy-dependencies-to-appimage)
(sh-or-die "wget" "https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage")
(sh-or-die "chmod" "+x" "appimagetool-x86_64.AppImage")
(sh-or-die "./appimagetool-x86_64.AppImage" "AppDir" "MidiEditor.AppImage")
