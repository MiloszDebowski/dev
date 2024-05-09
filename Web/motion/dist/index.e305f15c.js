// modules are defined as an array
// [ module function, map of requires ]
//
// map of requires is short require name -> numeric require
//
// anything defined in a previous bundle is accessed via the
// orig method which is the require for previous bundles

(function (modules, entry, mainEntry, parcelRequireName, globalName) {
  /* eslint-disable no-undef */
  var globalObject =
    typeof globalThis !== 'undefined'
      ? globalThis
      : typeof self !== 'undefined'
      ? self
      : typeof window !== 'undefined'
      ? window
      : typeof global !== 'undefined'
      ? global
      : {};
  /* eslint-enable no-undef */

  // Save the require from previous bundle to this closure if any
  var previousRequire =
    typeof globalObject[parcelRequireName] === 'function' &&
    globalObject[parcelRequireName];

  var cache = previousRequire.cache || {};
  // Do not use `require` to prevent Webpack from trying to bundle this call
  var nodeRequire =
    typeof module !== 'undefined' &&
    typeof module.require === 'function' &&
    module.require.bind(module);

  function newRequire(name, jumped) {
    if (!cache[name]) {
      if (!modules[name]) {
        // if we cannot find the module within our internal map or
        // cache jump to the current global require ie. the last bundle
        // that was added to the page.
        var currentRequire =
          typeof globalObject[parcelRequireName] === 'function' &&
          globalObject[parcelRequireName];
        if (!jumped && currentRequire) {
          return currentRequire(name, true);
        }

        // If there are other bundles on this page the require from the
        // previous one is saved to 'previousRequire'. Repeat this as
        // many times as there are bundles until the module is found or
        // we exhaust the require chain.
        if (previousRequire) {
          return previousRequire(name, true);
        }

        // Try the node require function if it exists.
        if (nodeRequire && typeof name === 'string') {
          return nodeRequire(name);
        }

        var err = new Error("Cannot find module '" + name + "'");
        err.code = 'MODULE_NOT_FOUND';
        throw err;
      }

      localRequire.resolve = resolve;
      localRequire.cache = {};

      var module = (cache[name] = new newRequire.Module(name));

      modules[name][0].call(
        module.exports,
        localRequire,
        module,
        module.exports,
        this
      );
    }

    return cache[name].exports;

    function localRequire(x) {
      var res = localRequire.resolve(x);
      return res === false ? {} : newRequire(res);
    }

    function resolve(x) {
      var id = modules[name][1][x];
      return id != null ? id : x;
    }
  }

  function Module(moduleName) {
    this.id = moduleName;
    this.bundle = newRequire;
    this.exports = {};
  }

  newRequire.isParcelRequire = true;
  newRequire.Module = Module;
  newRequire.modules = modules;
  newRequire.cache = cache;
  newRequire.parent = previousRequire;
  newRequire.register = function (id, exports) {
    modules[id] = [
      function (require, module) {
        module.exports = exports;
      },
      {},
    ];
  };

  Object.defineProperty(newRequire, 'root', {
    get: function () {
      return globalObject[parcelRequireName];
    },
  });

  globalObject[parcelRequireName] = newRequire;

  for (var i = 0; i < entry.length; i++) {
    newRequire(entry[i]);
  }

  if (mainEntry) {
    // Expose entry point to Node, AMD or browser globals
    // Based on https://github.com/ForbesLindesay/umd/blob/master/template.js
    var mainExports = newRequire(mainEntry);

    // CommonJS
    if (typeof exports === 'object' && typeof module !== 'undefined') {
      module.exports = mainExports;

      // RequireJS
    } else if (typeof define === 'function' && define.amd) {
      define(function () {
        return mainExports;
      });

      // <script>
    } else if (globalName) {
      this[globalName] = mainExports;
    }
  }
})({"1Jmog":[function(require,module,exports) {
var global = arguments[3];
var HMR_HOST = null;
var HMR_PORT = null;
var HMR_SECURE = false;
var HMR_ENV_HASH = "d6ea1d42532a7575";
var HMR_USE_SSE = false;
module.bundle.HMR_BUNDLE_ID = "bb2c04eee305f15c";
"use strict";
/* global HMR_HOST, HMR_PORT, HMR_ENV_HASH, HMR_SECURE, HMR_USE_SSE, chrome, browser, __parcel__import__, __parcel__importScripts__, ServiceWorkerGlobalScope */ /*::
import type {
  HMRAsset,
  HMRMessage,
} from '@parcel/reporter-dev-server/src/HMRServer.js';
interface ParcelRequire {
  (string): mixed;
  cache: {|[string]: ParcelModule|};
  hotData: {|[string]: mixed|};
  Module: any;
  parent: ?ParcelRequire;
  isParcelRequire: true;
  modules: {|[string]: [Function, {|[string]: string|}]|};
  HMR_BUNDLE_ID: string;
  root: ParcelRequire;
}
interface ParcelModule {
  hot: {|
    data: mixed,
    accept(cb: (Function) => void): void,
    dispose(cb: (mixed) => void): void,
    // accept(deps: Array<string> | string, cb: (Function) => void): void,
    // decline(): void,
    _acceptCallbacks: Array<(Function) => void>,
    _disposeCallbacks: Array<(mixed) => void>,
  |};
}
interface ExtensionContext {
  runtime: {|
    reload(): void,
    getURL(url: string): string;
    getManifest(): {manifest_version: number, ...};
  |};
}
declare var module: {bundle: ParcelRequire, ...};
declare var HMR_HOST: string;
declare var HMR_PORT: string;
declare var HMR_ENV_HASH: string;
declare var HMR_SECURE: boolean;
declare var HMR_USE_SSE: boolean;
declare var chrome: ExtensionContext;
declare var browser: ExtensionContext;
declare var __parcel__import__: (string) => Promise<void>;
declare var __parcel__importScripts__: (string) => Promise<void>;
declare var globalThis: typeof self;
declare var ServiceWorkerGlobalScope: Object;
*/ var OVERLAY_ID = "__parcel__error__overlay__";
var OldModule = module.bundle.Module;
function Module(moduleName) {
    OldModule.call(this, moduleName);
    this.hot = {
        data: module.bundle.hotData[moduleName],
        _acceptCallbacks: [],
        _disposeCallbacks: [],
        accept: function(fn) {
            this._acceptCallbacks.push(fn || function() {});
        },
        dispose: function(fn) {
            this._disposeCallbacks.push(fn);
        }
    };
    module.bundle.hotData[moduleName] = undefined;
}
module.bundle.Module = Module;
module.bundle.hotData = {};
var checkedAssets /*: {|[string]: boolean|} */ , assetsToDispose /*: Array<[ParcelRequire, string]> */ , assetsToAccept /*: Array<[ParcelRequire, string]> */ ;
function getHostname() {
    return HMR_HOST || (location.protocol.indexOf("http") === 0 ? location.hostname : "localhost");
}
function getPort() {
    return HMR_PORT || location.port;
}
// eslint-disable-next-line no-redeclare
var parent = module.bundle.parent;
if ((!parent || !parent.isParcelRequire) && typeof WebSocket !== "undefined") {
    var hostname = getHostname();
    var port = getPort();
    var protocol = HMR_SECURE || location.protocol == "https:" && ![
        "localhost",
        "127.0.0.1",
        "0.0.0.0"
    ].includes(hostname) ? "wss" : "ws";
    var ws;
    if (HMR_USE_SSE) ws = new EventSource("/__parcel_hmr");
    else try {
        ws = new WebSocket(protocol + "://" + hostname + (port ? ":" + port : "") + "/");
    } catch (err) {
        if (err.message) console.error(err.message);
        ws = {};
    }
    // Web extension context
    var extCtx = typeof browser === "undefined" ? typeof chrome === "undefined" ? null : chrome : browser;
    // Safari doesn't support sourceURL in error stacks.
    // eval may also be disabled via CSP, so do a quick check.
    var supportsSourceURL = false;
    try {
        (0, eval)('throw new Error("test"); //# sourceURL=test.js');
    } catch (err) {
        supportsSourceURL = err.stack.includes("test.js");
    }
    // $FlowFixMe
    ws.onmessage = async function(event /*: {data: string, ...} */ ) {
        checkedAssets = {} /*: {|[string]: boolean|} */ ;
        assetsToAccept = [];
        assetsToDispose = [];
        var data /*: HMRMessage */  = JSON.parse(event.data);
        if (data.type === "update") {
            // Remove error overlay if there is one
            if (typeof document !== "undefined") removeErrorOverlay();
            let assets = data.assets.filter((asset)=>asset.envHash === HMR_ENV_HASH);
            // Handle HMR Update
            let handled = assets.every((asset)=>{
                return asset.type === "css" || asset.type === "js" && hmrAcceptCheck(module.bundle.root, asset.id, asset.depsByBundle);
            });
            if (handled) {
                console.clear();
                // Dispatch custom event so other runtimes (e.g React Refresh) are aware.
                if (typeof window !== "undefined" && typeof CustomEvent !== "undefined") window.dispatchEvent(new CustomEvent("parcelhmraccept"));
                await hmrApplyUpdates(assets);
                // Dispose all old assets.
                let processedAssets = {} /*: {|[string]: boolean|} */ ;
                for(let i = 0; i < assetsToDispose.length; i++){
                    let id = assetsToDispose[i][1];
                    if (!processedAssets[id]) {
                        hmrDispose(assetsToDispose[i][0], id);
                        processedAssets[id] = true;
                    }
                }
                // Run accept callbacks. This will also re-execute other disposed assets in topological order.
                processedAssets = {};
                for(let i = 0; i < assetsToAccept.length; i++){
                    let id = assetsToAccept[i][1];
                    if (!processedAssets[id]) {
                        hmrAccept(assetsToAccept[i][0], id);
                        processedAssets[id] = true;
                    }
                }
            } else fullReload();
        }
        if (data.type === "error") {
            // Log parcel errors to console
            for (let ansiDiagnostic of data.diagnostics.ansi){
                let stack = ansiDiagnostic.codeframe ? ansiDiagnostic.codeframe : ansiDiagnostic.stack;
                console.error("\uD83D\uDEA8 [parcel]: " + ansiDiagnostic.message + "\n" + stack + "\n\n" + ansiDiagnostic.hints.join("\n"));
            }
            if (typeof document !== "undefined") {
                // Render the fancy html overlay
                removeErrorOverlay();
                var overlay = createErrorOverlay(data.diagnostics.html);
                // $FlowFixMe
                document.body.appendChild(overlay);
            }
        }
    };
    if (ws instanceof WebSocket) {
        ws.onerror = function(e) {
            if (e.message) console.error(e.message);
        };
        ws.onclose = function() {
            console.warn("[parcel] \uD83D\uDEA8 Connection to the HMR server was lost");
        };
    }
}
function removeErrorOverlay() {
    var overlay = document.getElementById(OVERLAY_ID);
    if (overlay) {
        overlay.remove();
        console.log("[parcel] \u2728 Error resolved");
    }
}
function createErrorOverlay(diagnostics) {
    var overlay = document.createElement("div");
    overlay.id = OVERLAY_ID;
    let errorHTML = '<div style="background: black; opacity: 0.85; font-size: 16px; color: white; position: fixed; height: 100%; width: 100%; top: 0px; left: 0px; padding: 30px; font-family: Menlo, Consolas, monospace; z-index: 9999;">';
    for (let diagnostic of diagnostics){
        let stack = diagnostic.frames.length ? diagnostic.frames.reduce((p, frame)=>{
            return `${p}
<a href="/__parcel_launch_editor?file=${encodeURIComponent(frame.location)}" style="text-decoration: underline; color: #888" onclick="fetch(this.href); return false">${frame.location}</a>
${frame.code}`;
        }, "") : diagnostic.stack;
        errorHTML += `
      <div>
        <div style="font-size: 18px; font-weight: bold; margin-top: 20px;">
          \u{1F6A8} ${diagnostic.message}
        </div>
        <pre>${stack}</pre>
        <div>
          ${diagnostic.hints.map((hint)=>"<div>\uD83D\uDCA1 " + hint + "</div>").join("")}
        </div>
        ${diagnostic.documentation ? `<div>\u{1F4DD} <a style="color: violet" href="${diagnostic.documentation}" target="_blank">Learn more</a></div>` : ""}
      </div>
    `;
    }
    errorHTML += "</div>";
    overlay.innerHTML = errorHTML;
    return overlay;
}
function fullReload() {
    if ("reload" in location) location.reload();
    else if (extCtx && extCtx.runtime && extCtx.runtime.reload) extCtx.runtime.reload();
}
function getParents(bundle, id) /*: Array<[ParcelRequire, string]> */ {
    var modules = bundle.modules;
    if (!modules) return [];
    var parents = [];
    var k, d, dep;
    for(k in modules)for(d in modules[k][1]){
        dep = modules[k][1][d];
        if (dep === id || Array.isArray(dep) && dep[dep.length - 1] === id) parents.push([
            bundle,
            k
        ]);
    }
    if (bundle.parent) parents = parents.concat(getParents(bundle.parent, id));
    return parents;
}
function updateLink(link) {
    var href = link.getAttribute("href");
    if (!href) return;
    var newLink = link.cloneNode();
    newLink.onload = function() {
        if (link.parentNode !== null) // $FlowFixMe
        link.parentNode.removeChild(link);
    };
    newLink.setAttribute("href", // $FlowFixMe
    href.split("?")[0] + "?" + Date.now());
    // $FlowFixMe
    link.parentNode.insertBefore(newLink, link.nextSibling);
}
var cssTimeout = null;
function reloadCSS() {
    if (cssTimeout) return;
    cssTimeout = setTimeout(function() {
        var links = document.querySelectorAll('link[rel="stylesheet"]');
        for(var i = 0; i < links.length; i++){
            // $FlowFixMe[incompatible-type]
            var href /*: string */  = links[i].getAttribute("href");
            var hostname = getHostname();
            var servedFromHMRServer = hostname === "localhost" ? new RegExp("^(https?:\\/\\/(0.0.0.0|127.0.0.1)|localhost):" + getPort()).test(href) : href.indexOf(hostname + ":" + getPort());
            var absolute = /^https?:\/\//i.test(href) && href.indexOf(location.origin) !== 0 && !servedFromHMRServer;
            if (!absolute) updateLink(links[i]);
        }
        cssTimeout = null;
    }, 50);
}
function hmrDownload(asset) {
    if (asset.type === "js") {
        if (typeof document !== "undefined") {
            let script = document.createElement("script");
            script.src = asset.url + "?t=" + Date.now();
            if (asset.outputFormat === "esmodule") script.type = "module";
            return new Promise((resolve, reject)=>{
                var _document$head;
                script.onload = ()=>resolve(script);
                script.onerror = reject;
                (_document$head = document.head) === null || _document$head === void 0 || _document$head.appendChild(script);
            });
        } else if (typeof importScripts === "function") {
            // Worker scripts
            if (asset.outputFormat === "esmodule") return import(asset.url + "?t=" + Date.now());
            else return new Promise((resolve, reject)=>{
                try {
                    importScripts(asset.url + "?t=" + Date.now());
                    resolve();
                } catch (err) {
                    reject(err);
                }
            });
        }
    }
}
async function hmrApplyUpdates(assets) {
    global.parcelHotUpdate = Object.create(null);
    let scriptsToRemove;
    try {
        // If sourceURL comments aren't supported in eval, we need to load
        // the update from the dev server over HTTP so that stack traces
        // are correct in errors/logs. This is much slower than eval, so
        // we only do it if needed (currently just Safari).
        // https://bugs.webkit.org/show_bug.cgi?id=137297
        // This path is also taken if a CSP disallows eval.
        if (!supportsSourceURL) {
            let promises = assets.map((asset)=>{
                var _hmrDownload;
                return (_hmrDownload = hmrDownload(asset)) === null || _hmrDownload === void 0 ? void 0 : _hmrDownload.catch((err)=>{
                    // Web extension fix
                    if (extCtx && extCtx.runtime && extCtx.runtime.getManifest().manifest_version == 3 && typeof ServiceWorkerGlobalScope != "undefined" && global instanceof ServiceWorkerGlobalScope) {
                        extCtx.runtime.reload();
                        return;
                    }
                    throw err;
                });
            });
            scriptsToRemove = await Promise.all(promises);
        }
        assets.forEach(function(asset) {
            hmrApply(module.bundle.root, asset);
        });
    } finally{
        delete global.parcelHotUpdate;
        if (scriptsToRemove) scriptsToRemove.forEach((script)=>{
            if (script) {
                var _document$head2;
                (_document$head2 = document.head) === null || _document$head2 === void 0 || _document$head2.removeChild(script);
            }
        });
    }
}
function hmrApply(bundle /*: ParcelRequire */ , asset /*:  HMRAsset */ ) {
    var modules = bundle.modules;
    if (!modules) return;
    if (asset.type === "css") reloadCSS();
    else if (asset.type === "js") {
        let deps = asset.depsByBundle[bundle.HMR_BUNDLE_ID];
        if (deps) {
            if (modules[asset.id]) {
                // Remove dependencies that are removed and will become orphaned.
                // This is necessary so that if the asset is added back again, the cache is gone, and we prevent a full page reload.
                let oldDeps = modules[asset.id][1];
                for(let dep in oldDeps)if (!deps[dep] || deps[dep] !== oldDeps[dep]) {
                    let id = oldDeps[dep];
                    let parents = getParents(module.bundle.root, id);
                    if (parents.length === 1) hmrDelete(module.bundle.root, id);
                }
            }
            if (supportsSourceURL) // Global eval. We would use `new Function` here but browser
            // support for source maps is better with eval.
            (0, eval)(asset.output);
            // $FlowFixMe
            let fn = global.parcelHotUpdate[asset.id];
            modules[asset.id] = [
                fn,
                deps
            ];
        } else if (bundle.parent) hmrApply(bundle.parent, asset);
    }
}
function hmrDelete(bundle, id) {
    let modules = bundle.modules;
    if (!modules) return;
    if (modules[id]) {
        // Collect dependencies that will become orphaned when this module is deleted.
        let deps = modules[id][1];
        let orphans = [];
        for(let dep in deps){
            let parents = getParents(module.bundle.root, deps[dep]);
            if (parents.length === 1) orphans.push(deps[dep]);
        }
        // Delete the module. This must be done before deleting dependencies in case of circular dependencies.
        delete modules[id];
        delete bundle.cache[id];
        // Now delete the orphans.
        orphans.forEach((id)=>{
            hmrDelete(module.bundle.root, id);
        });
    } else if (bundle.parent) hmrDelete(bundle.parent, id);
}
function hmrAcceptCheck(bundle /*: ParcelRequire */ , id /*: string */ , depsByBundle /*: ?{ [string]: { [string]: string } }*/ ) {
    if (hmrAcceptCheckOne(bundle, id, depsByBundle)) return true;
    // Traverse parents breadth first. All possible ancestries must accept the HMR update, or we'll reload.
    let parents = getParents(module.bundle.root, id);
    let accepted = false;
    while(parents.length > 0){
        let v = parents.shift();
        let a = hmrAcceptCheckOne(v[0], v[1], null);
        if (a) // If this parent accepts, stop traversing upward, but still consider siblings.
        accepted = true;
        else {
            // Otherwise, queue the parents in the next level upward.
            let p = getParents(module.bundle.root, v[1]);
            if (p.length === 0) {
                // If there are no parents, then we've reached an entry without accepting. Reload.
                accepted = false;
                break;
            }
            parents.push(...p);
        }
    }
    return accepted;
}
function hmrAcceptCheckOne(bundle /*: ParcelRequire */ , id /*: string */ , depsByBundle /*: ?{ [string]: { [string]: string } }*/ ) {
    var modules = bundle.modules;
    if (!modules) return;
    if (depsByBundle && !depsByBundle[bundle.HMR_BUNDLE_ID]) {
        // If we reached the root bundle without finding where the asset should go,
        // there's nothing to do. Mark as "accepted" so we don't reload the page.
        if (!bundle.parent) return true;
        return hmrAcceptCheck(bundle.parent, id, depsByBundle);
    }
    if (checkedAssets[id]) return true;
    checkedAssets[id] = true;
    var cached = bundle.cache[id];
    assetsToDispose.push([
        bundle,
        id
    ]);
    if (!cached || cached.hot && cached.hot._acceptCallbacks.length) {
        assetsToAccept.push([
            bundle,
            id
        ]);
        return true;
    }
}
function hmrDispose(bundle /*: ParcelRequire */ , id /*: string */ ) {
    var cached = bundle.cache[id];
    bundle.hotData[id] = {};
    if (cached && cached.hot) cached.hot.data = bundle.hotData[id];
    if (cached && cached.hot && cached.hot._disposeCallbacks.length) cached.hot._disposeCallbacks.forEach(function(cb) {
        cb(bundle.hotData[id]);
    });
    delete bundle.cache[id];
}
function hmrAccept(bundle /*: ParcelRequire */ , id /*: string */ ) {
    // Execute the module.
    bundle(id);
    // Run the accept callbacks in the new version of the module.
    var cached = bundle.cache[id];
    if (cached && cached.hot && cached.hot._acceptCallbacks.length) cached.hot._acceptCallbacks.forEach(function(cb) {
        var assetsToAlsoAccept = cb(function() {
            return getParents(module.bundle.root, id);
        });
        if (assetsToAlsoAccept && assetsToAccept.length) {
            assetsToAlsoAccept.forEach(function(a) {
                hmrDispose(a[0], a[1]);
            });
            // $FlowFixMe[method-unbinding]
            assetsToAccept.push.apply(assetsToAccept, assetsToAlsoAccept);
        }
    });
}

},{}],"fdzCV":[function(require,module,exports) {
const popmotion = require("2c79899260e08df0");
const ball = document.querySelector(".ball");
popmotion.animate({
    from: "0px",
    to: "20px",
    repeat: Infinity,
    repeatType: "reverse",
    type: "spring",
    onUpdate (update) {
        console.log(update);
        ball.style.top = update;
    }
});

},{"2c79899260e08df0":"iemqi"}],"iemqi":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "animate", ()=>(0, _indexMjs.animate));
parcelHelpers.export(exports, "inertia", ()=>(0, _inertiaMjs.inertia));
parcelHelpers.export(exports, "decay", ()=>(0, _decayMjs.decay));
parcelHelpers.export(exports, "spring", ()=>(0, _springMjs.spring));
parcelHelpers.export(exports, "keyframes", ()=>(0, _keyframesMjs.keyframes));
parcelHelpers.export(exports, "angle", ()=>(0, _angleMjs.angle));
parcelHelpers.export(exports, "applyOffset", ()=>(0, _applyOffsetMjs.applyOffset));
parcelHelpers.export(exports, "attract", ()=>(0, _attractMjs.attract));
parcelHelpers.export(exports, "attractExpo", ()=>(0, _attractMjs.attractExpo));
parcelHelpers.export(exports, "createAttractor", ()=>(0, _attractMjs.createAttractor));
parcelHelpers.export(exports, "clamp", ()=>(0, _clampMjs.clamp));
parcelHelpers.export(exports, "degreesToRadians", ()=>(0, _degreesToRadiansMjs.degreesToRadians));
parcelHelpers.export(exports, "distance", ()=>(0, _distanceMjs.distance));
parcelHelpers.export(exports, "interpolate", ()=>(0, _interpolateMjs.interpolate));
parcelHelpers.export(exports, "isPoint3D", ()=>(0, _isPoint3DMjs.isPoint3D));
parcelHelpers.export(exports, "isPoint", ()=>(0, _isPointMjs.isPoint));
parcelHelpers.export(exports, "mixColor", ()=>(0, _mixColorMjs.mixColor));
parcelHelpers.export(exports, "mixComplex", ()=>(0, _mixComplexMjs.mixComplex));
parcelHelpers.export(exports, "mix", ()=>(0, _mixMjs.mix));
parcelHelpers.export(exports, "pipe", ()=>(0, _pipeMjs.pipe));
parcelHelpers.export(exports, "pointFromVector", ()=>(0, _pointFromVectorMjs.pointFromVector));
parcelHelpers.export(exports, "progress", ()=>(0, _progressMjs.progress));
parcelHelpers.export(exports, "radiansToDegrees", ()=>(0, _radiansToDegreesMjs.radiansToDegrees));
parcelHelpers.export(exports, "smoothFrame", ()=>(0, _smoothFrameMjs.smoothFrame));
parcelHelpers.export(exports, "smooth", ()=>(0, _smoothMjs.smooth));
parcelHelpers.export(exports, "snap", ()=>(0, _snapMjs.snap));
parcelHelpers.export(exports, "toDecimal", ()=>(0, _toDecimalMjs.toDecimal));
parcelHelpers.export(exports, "velocityPerFrame", ()=>(0, _velocityPerFrameMjs.velocityPerFrame));
parcelHelpers.export(exports, "velocityPerSecond", ()=>(0, _velocityPerSecondMjs.velocityPerSecond));
parcelHelpers.export(exports, "wrap", ()=>(0, _wrapMjs.wrap));
parcelHelpers.export(exports, "anticipate", ()=>(0, _indexMjs1.anticipate));
parcelHelpers.export(exports, "backIn", ()=>(0, _indexMjs1.backIn));
parcelHelpers.export(exports, "backInOut", ()=>(0, _indexMjs1.backInOut));
parcelHelpers.export(exports, "backOut", ()=>(0, _indexMjs1.backOut));
parcelHelpers.export(exports, "bounceIn", ()=>(0, _indexMjs1.bounceIn));
parcelHelpers.export(exports, "bounceInOut", ()=>(0, _indexMjs1.bounceInOut));
parcelHelpers.export(exports, "bounceOut", ()=>(0, _indexMjs1.bounceOut));
parcelHelpers.export(exports, "circIn", ()=>(0, _indexMjs1.circIn));
parcelHelpers.export(exports, "circInOut", ()=>(0, _indexMjs1.circInOut));
parcelHelpers.export(exports, "circOut", ()=>(0, _indexMjs1.circOut));
parcelHelpers.export(exports, "easeIn", ()=>(0, _indexMjs1.easeIn));
parcelHelpers.export(exports, "easeInOut", ()=>(0, _indexMjs1.easeInOut));
parcelHelpers.export(exports, "easeOut", ()=>(0, _indexMjs1.easeOut));
parcelHelpers.export(exports, "linear", ()=>(0, _indexMjs1.linear));
parcelHelpers.export(exports, "cubicBezier", ()=>(0, _cubicBezierMjs.cubicBezier));
parcelHelpers.export(exports, "steps", ()=>(0, _stepsMjs.steps));
parcelHelpers.export(exports, "createAnticipate", ()=>(0, _utilsMjs.createAnticipate));
parcelHelpers.export(exports, "createBackIn", ()=>(0, _utilsMjs.createBackIn));
parcelHelpers.export(exports, "createExpoIn", ()=>(0, _utilsMjs.createExpoIn));
parcelHelpers.export(exports, "mirrorEasing", ()=>(0, _utilsMjs.mirrorEasing));
parcelHelpers.export(exports, "reverseEasing", ()=>(0, _utilsMjs.reverseEasing));
var _indexMjs = require("./animations/index.mjs");
var _inertiaMjs = require("./animations/inertia.mjs");
var _decayMjs = require("./animations/generators/decay.mjs");
var _springMjs = require("./animations/generators/spring.mjs");
var _keyframesMjs = require("./animations/generators/keyframes.mjs");
var _angleMjs = require("./utils/angle.mjs");
var _applyOffsetMjs = require("./utils/apply-offset.mjs");
var _attractMjs = require("./utils/attract.mjs");
var _clampMjs = require("./utils/clamp.mjs");
var _degreesToRadiansMjs = require("./utils/degrees-to-radians.mjs");
var _distanceMjs = require("./utils/distance.mjs");
var _interpolateMjs = require("./utils/interpolate.mjs");
var _isPoint3DMjs = require("./utils/is-point-3d.mjs");
var _isPointMjs = require("./utils/is-point.mjs");
var _mixColorMjs = require("./utils/mix-color.mjs");
var _mixComplexMjs = require("./utils/mix-complex.mjs");
var _mixMjs = require("./utils/mix.mjs");
var _pipeMjs = require("./utils/pipe.mjs");
var _pointFromVectorMjs = require("./utils/point-from-vector.mjs");
var _progressMjs = require("./utils/progress.mjs");
var _radiansToDegreesMjs = require("./utils/radians-to-degrees.mjs");
var _smoothFrameMjs = require("./utils/smooth-frame.mjs");
var _smoothMjs = require("./utils/smooth.mjs");
var _snapMjs = require("./utils/snap.mjs");
var _toDecimalMjs = require("./utils/to-decimal.mjs");
var _velocityPerFrameMjs = require("./utils/velocity-per-frame.mjs");
var _velocityPerSecondMjs = require("./utils/velocity-per-second.mjs");
var _wrapMjs = require("./utils/wrap.mjs");
var _indexMjs1 = require("./easing/index.mjs");
var _cubicBezierMjs = require("./easing/cubic-bezier.mjs");
var _stepsMjs = require("./easing/steps.mjs");
var _utilsMjs = require("./easing/utils.mjs");

},{"./animations/index.mjs":"a5fCk","./animations/inertia.mjs":"dSGIQ","./animations/generators/decay.mjs":"apvaq","./animations/generators/spring.mjs":"oDSOo","./animations/generators/keyframes.mjs":"4AWeA","./utils/angle.mjs":"bOLME","./utils/apply-offset.mjs":"lKx1t","./utils/attract.mjs":"cWCzY","./utils/clamp.mjs":"Y4sdh","./utils/degrees-to-radians.mjs":"jBUWN","./utils/distance.mjs":"9yHdu","./utils/interpolate.mjs":"9axN1","./utils/is-point-3d.mjs":"immOm","./utils/is-point.mjs":"8eQlh","./utils/mix-color.mjs":"03T1w","./utils/mix-complex.mjs":"bRXYN","./utils/mix.mjs":"23SEC","./utils/pipe.mjs":"hg0kf","./utils/point-from-vector.mjs":"7GM9Y","./utils/progress.mjs":"d01Ia","./utils/radians-to-degrees.mjs":"g2UIl","./utils/smooth-frame.mjs":"54WVZ","./utils/smooth.mjs":"ctKTV","./utils/snap.mjs":"8RBoK","./utils/to-decimal.mjs":"irLx9","./utils/velocity-per-frame.mjs":"jKe2m","./utils/velocity-per-second.mjs":"2WHye","./utils/wrap.mjs":"aG282","./easing/index.mjs":"lSPVQ","./easing/cubic-bezier.mjs":"7SHvB","./easing/steps.mjs":"fQk8J","./easing/utils.mjs":"2LkwN","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"a5fCk":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "animate", ()=>animate);
var _tslib = require("tslib");
var _detectAnimationFromOptionsMjs = require("./utils/detect-animation-from-options.mjs");
var _framesync = require("framesync");
var _framesyncDefault = parcelHelpers.interopDefault(_framesync);
var _interpolateMjs = require("../utils/interpolate.mjs");
var _elapsedMjs = require("./utils/elapsed.mjs");
const framesync = (update)=>{
    const passTimestamp = ({ delta })=>update(delta);
    return {
        start: ()=>(0, _framesyncDefault.default).update(passTimestamp, true),
        stop: ()=>(0, _framesync.cancelSync).update(passTimestamp)
    };
};
function animate(_a) {
    var _b, _c;
    var { from, autoplay = true, driver = framesync, elapsed = 0, repeat: repeatMax = 0, repeatType = "loop", repeatDelay = 0, onPlay, onStop, onComplete, onRepeat, onUpdate } = _a, options = (0, _tslib.__rest)(_a, [
        "from",
        "autoplay",
        "driver",
        "elapsed",
        "repeat",
        "repeatType",
        "repeatDelay",
        "onPlay",
        "onStop",
        "onComplete",
        "onRepeat",
        "onUpdate"
    ]);
    let { to } = options;
    let driverControls;
    let repeatCount = 0;
    let computedDuration = options.duration;
    let latest;
    let isComplete = false;
    let isForwardPlayback = true;
    let interpolateFromNumber;
    const animator = (0, _detectAnimationFromOptionsMjs.detectAnimationFromOptions)(options);
    if ((_c = (_b = animator).needsInterpolation) === null || _c === void 0 ? void 0 : _c.call(_b, from, to)) {
        interpolateFromNumber = (0, _interpolateMjs.interpolate)([
            0,
            100
        ], [
            from,
            to
        ], {
            clamp: false
        });
        from = 0;
        to = 100;
    }
    const animation = animator(Object.assign(Object.assign({}, options), {
        from,
        to
    }));
    function repeat() {
        repeatCount++;
        if (repeatType === "reverse") {
            isForwardPlayback = repeatCount % 2 === 0;
            elapsed = (0, _elapsedMjs.reverseElapsed)(elapsed, computedDuration, repeatDelay, isForwardPlayback);
        } else {
            elapsed = (0, _elapsedMjs.loopElapsed)(elapsed, computedDuration, repeatDelay);
            if (repeatType === "mirror") animation.flipTarget();
        }
        isComplete = false;
        onRepeat && onRepeat();
    }
    function complete() {
        driverControls.stop();
        onComplete && onComplete();
    }
    function update(delta) {
        if (!isForwardPlayback) delta = -delta;
        elapsed += delta;
        if (!isComplete) {
            const state = animation.next(Math.max(0, elapsed));
            latest = state.value;
            if (interpolateFromNumber) latest = interpolateFromNumber(latest);
            isComplete = isForwardPlayback ? state.done : elapsed <= 0;
        }
        onUpdate === null || onUpdate === void 0 || onUpdate(latest);
        if (isComplete) {
            if (repeatCount === 0) computedDuration !== null && computedDuration !== void 0 ? computedDuration : computedDuration = elapsed;
            if (repeatCount < repeatMax) (0, _elapsedMjs.hasRepeatDelayElapsed)(elapsed, computedDuration, repeatDelay, isForwardPlayback) && repeat();
            else complete();
        }
    }
    function play() {
        onPlay === null || onPlay === void 0 || onPlay();
        driverControls = driver(update);
        driverControls.start();
    }
    autoplay && play();
    return {
        stop: ()=>{
            onStop === null || onStop === void 0 || onStop();
            driverControls.stop();
        }
    };
}

},{"tslib":"lRdW5","./utils/detect-animation-from-options.mjs":"c0lgA","framesync":"lhfBw","../utils/interpolate.mjs":"9axN1","./utils/elapsed.mjs":"bYEeZ","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"lRdW5":[function(require,module,exports) {
/******************************************************************************
Copyright (c) Microsoft Corporation.

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
***************************************************************************** */ /* global Reflect, Promise */ var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "__extends", ()=>__extends);
parcelHelpers.export(exports, "__assign", ()=>__assign);
parcelHelpers.export(exports, "__rest", ()=>__rest);
parcelHelpers.export(exports, "__decorate", ()=>__decorate);
parcelHelpers.export(exports, "__param", ()=>__param);
parcelHelpers.export(exports, "__metadata", ()=>__metadata);
parcelHelpers.export(exports, "__awaiter", ()=>__awaiter);
parcelHelpers.export(exports, "__generator", ()=>__generator);
parcelHelpers.export(exports, "__createBinding", ()=>__createBinding);
parcelHelpers.export(exports, "__exportStar", ()=>__exportStar);
parcelHelpers.export(exports, "__values", ()=>__values);
parcelHelpers.export(exports, "__read", ()=>__read);
/** @deprecated */ parcelHelpers.export(exports, "__spread", ()=>__spread);
/** @deprecated */ parcelHelpers.export(exports, "__spreadArrays", ()=>__spreadArrays);
parcelHelpers.export(exports, "__spreadArray", ()=>__spreadArray);
parcelHelpers.export(exports, "__await", ()=>__await);
parcelHelpers.export(exports, "__asyncGenerator", ()=>__asyncGenerator);
parcelHelpers.export(exports, "__asyncDelegator", ()=>__asyncDelegator);
parcelHelpers.export(exports, "__asyncValues", ()=>__asyncValues);
parcelHelpers.export(exports, "__makeTemplateObject", ()=>__makeTemplateObject);
parcelHelpers.export(exports, "__importStar", ()=>__importStar);
parcelHelpers.export(exports, "__importDefault", ()=>__importDefault);
parcelHelpers.export(exports, "__classPrivateFieldGet", ()=>__classPrivateFieldGet);
parcelHelpers.export(exports, "__classPrivateFieldSet", ()=>__classPrivateFieldSet);
parcelHelpers.export(exports, "__classPrivateFieldIn", ()=>__classPrivateFieldIn);
var extendStatics = function(d, b) {
    extendStatics = Object.setPrototypeOf || ({
        __proto__: []
    }) instanceof Array && function(d, b) {
        d.__proto__ = b;
    } || function(d, b) {
        for(var p in b)if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p];
    };
    return extendStatics(d, b);
};
function __extends(d, b) {
    if (typeof b !== "function" && b !== null) throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
    extendStatics(d, b);
    function __() {
        this.constructor = d;
    }
    d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
}
var __assign = function() {
    __assign = Object.assign || function __assign(t) {
        for(var s, i = 1, n = arguments.length; i < n; i++){
            s = arguments[i];
            for(var p in s)if (Object.prototype.hasOwnProperty.call(s, p)) t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
function __rest(s, e) {
    var t = {};
    for(var p in s)if (Object.prototype.hasOwnProperty.call(s, p) && e.indexOf(p) < 0) t[p] = s[p];
    if (s != null && typeof Object.getOwnPropertySymbols === "function") {
        for(var i = 0, p = Object.getOwnPropertySymbols(s); i < p.length; i++)if (e.indexOf(p[i]) < 0 && Object.prototype.propertyIsEnumerable.call(s, p[i])) t[p[i]] = s[p[i]];
    }
    return t;
}
function __decorate(decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for(var i = decorators.length - 1; i >= 0; i--)if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
}
function __param(paramIndex, decorator) {
    return function(target, key) {
        decorator(target, key, paramIndex);
    };
}
function __metadata(metadataKey, metadataValue) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(metadataKey, metadataValue);
}
function __awaiter(thisArg, _arguments, P, generator) {
    function adopt(value) {
        return value instanceof P ? value : new P(function(resolve) {
            resolve(value);
        });
    }
    return new (P || (P = Promise))(function(resolve, reject) {
        function fulfilled(value) {
            try {
                step(generator.next(value));
            } catch (e) {
                reject(e);
            }
        }
        function rejected(value) {
            try {
                step(generator["throw"](value));
            } catch (e) {
                reject(e);
            }
        }
        function step(result) {
            result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected);
        }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
}
function __generator(thisArg, body) {
    var _ = {
        label: 0,
        sent: function() {
            if (t[0] & 1) throw t[1];
            return t[1];
        },
        trys: [],
        ops: []
    }, f, y, t, g;
    return g = {
        next: verb(0),
        "throw": verb(1),
        "return": verb(2)
    }, typeof Symbol === "function" && (g[Symbol.iterator] = function() {
        return this;
    }), g;
    function verb(n) {
        return function(v) {
            return step([
                n,
                v
            ]);
        };
    }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while(_)try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [
                op[0] & 2,
                t.value
            ];
            switch(op[0]){
                case 0:
                case 1:
                    t = op;
                    break;
                case 4:
                    _.label++;
                    return {
                        value: op[1],
                        done: false
                    };
                case 5:
                    _.label++;
                    y = op[1];
                    op = [
                        0
                    ];
                    continue;
                case 7:
                    op = _.ops.pop();
                    _.trys.pop();
                    continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) {
                        _ = 0;
                        continue;
                    }
                    if (op[0] === 3 && (!t || op[1] > t[0] && op[1] < t[3])) {
                        _.label = op[1];
                        break;
                    }
                    if (op[0] === 6 && _.label < t[1]) {
                        _.label = t[1];
                        t = op;
                        break;
                    }
                    if (t && _.label < t[2]) {
                        _.label = t[2];
                        _.ops.push(op);
                        break;
                    }
                    if (t[2]) _.ops.pop();
                    _.trys.pop();
                    continue;
            }
            op = body.call(thisArg, _);
        } catch (e) {
            op = [
                6,
                e
            ];
            y = 0;
        } finally{
            f = t = 0;
        }
        if (op[0] & 5) throw op[1];
        return {
            value: op[0] ? op[1] : void 0,
            done: true
        };
    }
}
var __createBinding = Object.create ? function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) desc = {
        enumerable: true,
        get: function() {
            return m[k];
        }
    };
    Object.defineProperty(o, k2, desc);
} : function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
};
function __exportStar(m, o) {
    for(var p in m)if (p !== "default" && !Object.prototype.hasOwnProperty.call(o, p)) __createBinding(o, m, p);
}
function __values(o) {
    var s = typeof Symbol === "function" && Symbol.iterator, m = s && o[s], i = 0;
    if (m) return m.call(o);
    if (o && typeof o.length === "number") return {
        next: function() {
            if (o && i >= o.length) o = void 0;
            return {
                value: o && o[i++],
                done: !o
            };
        }
    };
    throw new TypeError(s ? "Object is not iterable." : "Symbol.iterator is not defined.");
}
function __read(o, n) {
    var m = typeof Symbol === "function" && o[Symbol.iterator];
    if (!m) return o;
    var i = m.call(o), r, ar = [], e;
    try {
        while((n === void 0 || n-- > 0) && !(r = i.next()).done)ar.push(r.value);
    } catch (error) {
        e = {
            error: error
        };
    } finally{
        try {
            if (r && !r.done && (m = i["return"])) m.call(i);
        } finally{
            if (e) throw e.error;
        }
    }
    return ar;
}
function __spread() {
    for(var ar = [], i = 0; i < arguments.length; i++)ar = ar.concat(__read(arguments[i]));
    return ar;
}
function __spreadArrays() {
    for(var s = 0, i = 0, il = arguments.length; i < il; i++)s += arguments[i].length;
    for(var r = Array(s), k = 0, i = 0; i < il; i++)for(var a = arguments[i], j = 0, jl = a.length; j < jl; j++, k++)r[k] = a[j];
    return r;
}
function __spreadArray(to, from, pack) {
    if (pack || arguments.length === 2) {
        for(var i = 0, l = from.length, ar; i < l; i++)if (ar || !(i in from)) {
            if (!ar) ar = Array.prototype.slice.call(from, 0, i);
            ar[i] = from[i];
        }
    }
    return to.concat(ar || Array.prototype.slice.call(from));
}
function __await(v) {
    return this instanceof __await ? (this.v = v, this) : new __await(v);
}
function __asyncGenerator(thisArg, _arguments, generator) {
    if (!Symbol.asyncIterator) throw new TypeError("Symbol.asyncIterator is not defined.");
    var g = generator.apply(thisArg, _arguments || []), i, q = [];
    return i = {}, verb("next"), verb("throw"), verb("return"), i[Symbol.asyncIterator] = function() {
        return this;
    }, i;
    function verb(n) {
        if (g[n]) i[n] = function(v) {
            return new Promise(function(a, b) {
                q.push([
                    n,
                    v,
                    a,
                    b
                ]) > 1 || resume(n, v);
            });
        };
    }
    function resume(n, v) {
        try {
            step(g[n](v));
        } catch (e) {
            settle(q[0][3], e);
        }
    }
    function step(r) {
        r.value instanceof __await ? Promise.resolve(r.value.v).then(fulfill, reject) : settle(q[0][2], r);
    }
    function fulfill(value) {
        resume("next", value);
    }
    function reject(value) {
        resume("throw", value);
    }
    function settle(f, v) {
        if (f(v), q.shift(), q.length) resume(q[0][0], q[0][1]);
    }
}
function __asyncDelegator(o) {
    var i, p;
    return i = {}, verb("next"), verb("throw", function(e) {
        throw e;
    }), verb("return"), i[Symbol.iterator] = function() {
        return this;
    }, i;
    function verb(n, f) {
        i[n] = o[n] ? function(v) {
            return (p = !p) ? {
                value: __await(o[n](v)),
                done: n === "return"
            } : f ? f(v) : v;
        } : f;
    }
}
function __asyncValues(o) {
    if (!Symbol.asyncIterator) throw new TypeError("Symbol.asyncIterator is not defined.");
    var m = o[Symbol.asyncIterator], i;
    return m ? m.call(o) : (o = typeof __values === "function" ? __values(o) : o[Symbol.iterator](), i = {}, verb("next"), verb("throw"), verb("return"), i[Symbol.asyncIterator] = function() {
        return this;
    }, i);
    function verb(n) {
        i[n] = o[n] && function(v) {
            return new Promise(function(resolve, reject) {
                v = o[n](v), settle(resolve, reject, v.done, v.value);
            });
        };
    }
    function settle(resolve, reject, d, v) {
        Promise.resolve(v).then(function(v) {
            resolve({
                value: v,
                done: d
            });
        }, reject);
    }
}
function __makeTemplateObject(cooked, raw) {
    if (Object.defineProperty) Object.defineProperty(cooked, "raw", {
        value: raw
    });
    else cooked.raw = raw;
    return cooked;
}
var __setModuleDefault = Object.create ? function(o, v) {
    Object.defineProperty(o, "default", {
        enumerable: true,
        value: v
    });
} : function(o, v) {
    o["default"] = v;
};
function __importStar(mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) {
        for(var k in mod)if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    }
    __setModuleDefault(result, mod);
    return result;
}
function __importDefault(mod) {
    return mod && mod.__esModule ? mod : {
        default: mod
    };
}
function __classPrivateFieldGet(receiver, state, kind, f) {
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a getter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot read private member from an object whose class did not declare it");
    return kind === "m" ? f : kind === "a" ? f.call(receiver) : f ? f.value : state.get(receiver);
}
function __classPrivateFieldSet(receiver, state, value, kind, f) {
    if (kind === "m") throw new TypeError("Private method is not writable");
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a setter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot write private member to an object whose class did not declare it");
    return kind === "a" ? f.call(receiver, value) : f ? f.value = value : state.set(receiver, value), value;
}
function __classPrivateFieldIn(state, receiver) {
    if (receiver === null || typeof receiver !== "object" && typeof receiver !== "function") throw new TypeError("Cannot use 'in' operator on non-object");
    return typeof state === "function" ? receiver === state : state.has(receiver);
}

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"61w1T":[function(require,module,exports) {
exports.interopDefault = function(a) {
    return a && a.__esModule ? a : {
        default: a
    };
};
exports.defineInteropFlag = function(a) {
    Object.defineProperty(a, "__esModule", {
        value: true
    });
};
exports.exportAll = function(source, dest) {
    Object.keys(source).forEach(function(key) {
        if (key === "default" || key === "__esModule" || Object.prototype.hasOwnProperty.call(dest, key)) return;
        Object.defineProperty(dest, key, {
            enumerable: true,
            get: function() {
                return source[key];
            }
        });
    });
    return dest;
};
exports.export = function(dest, destName, get) {
    Object.defineProperty(dest, destName, {
        enumerable: true,
        get: get
    });
};

},{}],"c0lgA":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "detectAnimationFromOptions", ()=>detectAnimationFromOptions);
var _springMjs = require("../generators/spring.mjs");
var _keyframesMjs = require("../generators/keyframes.mjs");
var _decayMjs = require("../generators/decay.mjs");
const types = {
    keyframes: (0, _keyframesMjs.keyframes),
    spring: (0, _springMjs.spring),
    decay: (0, _decayMjs.decay)
};
function detectAnimationFromOptions(config) {
    if (Array.isArray(config.to)) return 0, _keyframesMjs.keyframes;
    else if (types[config.type]) return types[config.type];
    const keys = new Set(Object.keys(config));
    if (keys.has("ease") || keys.has("duration") && !keys.has("dampingRatio")) return 0, _keyframesMjs.keyframes;
    else if (keys.has("dampingRatio") || keys.has("stiffness") || keys.has("mass") || keys.has("damping") || keys.has("restSpeed") || keys.has("restDelta")) return 0, _springMjs.spring;
    return 0, _keyframesMjs.keyframes;
}

},{"../generators/spring.mjs":"oDSOo","../generators/keyframes.mjs":"4AWeA","../generators/decay.mjs":"apvaq","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"oDSOo":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "spring", ()=>spring);
var _tslib = require("tslib");
var _findSpringMjs = require("../utils/find-spring.mjs");
const durationKeys = [
    "duration",
    "bounce"
];
const physicsKeys = [
    "stiffness",
    "damping",
    "mass"
];
function isSpringType(options, keys) {
    return keys.some((key)=>options[key] !== undefined);
}
function getSpringOptions(options) {
    let springOptions = Object.assign({
        velocity: 0.0,
        stiffness: 100,
        damping: 10,
        mass: 1.0,
        isResolvedFromDuration: false
    }, options);
    if (!isSpringType(options, physicsKeys) && isSpringType(options, durationKeys)) {
        const derived = (0, _findSpringMjs.findSpring)(options);
        springOptions = Object.assign(Object.assign(Object.assign({}, springOptions), derived), {
            velocity: 0.0,
            mass: 1.0
        });
        springOptions.isResolvedFromDuration = true;
    }
    return springOptions;
}
function spring(_a) {
    var { from = 0.0, to = 1.0, restSpeed = 2, restDelta } = _a, options = (0, _tslib.__rest)(_a, [
        "from",
        "to",
        "restSpeed",
        "restDelta"
    ]);
    const state = {
        done: false,
        value: from
    };
    let { stiffness, damping, mass, velocity, duration, isResolvedFromDuration } = getSpringOptions(options);
    let resolveSpring = zero;
    let resolveVelocity = zero;
    function createSpring() {
        const initialVelocity = velocity ? -(velocity / 1000) : 0.0;
        const initialDelta = to - from;
        const dampingRatio = damping / (2 * Math.sqrt(stiffness * mass));
        const undampedAngularFreq = Math.sqrt(stiffness / mass) / 1000;
        if (restDelta === undefined) restDelta = Math.min(Math.abs(to - from) / 100, 0.4);
        if (dampingRatio < 1) {
            const angularFreq = (0, _findSpringMjs.calcAngularFreq)(undampedAngularFreq, dampingRatio);
            resolveSpring = (t)=>{
                const envelope = Math.exp(-dampingRatio * undampedAngularFreq * t);
                return to - envelope * ((initialVelocity + dampingRatio * undampedAngularFreq * initialDelta) / angularFreq * Math.sin(angularFreq * t) + initialDelta * Math.cos(angularFreq * t));
            };
            resolveVelocity = (t)=>{
                const envelope = Math.exp(-dampingRatio * undampedAngularFreq * t);
                return dampingRatio * undampedAngularFreq * envelope * (Math.sin(angularFreq * t) * (initialVelocity + dampingRatio * undampedAngularFreq * initialDelta) / angularFreq + initialDelta * Math.cos(angularFreq * t)) - envelope * (Math.cos(angularFreq * t) * (initialVelocity + dampingRatio * undampedAngularFreq * initialDelta) - angularFreq * initialDelta * Math.sin(angularFreq * t));
            };
        } else if (dampingRatio === 1) resolveSpring = (t)=>to - Math.exp(-undampedAngularFreq * t) * (initialDelta + (initialVelocity + undampedAngularFreq * initialDelta) * t);
        else {
            const dampedAngularFreq = undampedAngularFreq * Math.sqrt(dampingRatio * dampingRatio - 1);
            resolveSpring = (t)=>{
                const envelope = Math.exp(-dampingRatio * undampedAngularFreq * t);
                const freqForT = Math.min(dampedAngularFreq * t, 300);
                return to - envelope * ((initialVelocity + dampingRatio * undampedAngularFreq * initialDelta) * Math.sinh(freqForT) + dampedAngularFreq * initialDelta * Math.cosh(freqForT)) / dampedAngularFreq;
            };
        }
    }
    createSpring();
    return {
        next: (t)=>{
            const current = resolveSpring(t);
            if (!isResolvedFromDuration) {
                const currentVelocity = resolveVelocity(t) * 1000;
                const isBelowVelocityThreshold = Math.abs(currentVelocity) <= restSpeed;
                const isBelowDisplacementThreshold = Math.abs(to - current) <= restDelta;
                state.done = isBelowVelocityThreshold && isBelowDisplacementThreshold;
            } else state.done = t >= duration;
            state.value = state.done ? to : current;
            return state;
        },
        flipTarget: ()=>{
            velocity = -velocity;
            [from, to] = [
                to,
                from
            ];
            createSpring();
        }
    };
}
spring.needsInterpolation = (a, b)=>typeof a === "string" || typeof b === "string";
const zero = (_t)=>0;

},{"tslib":"lRdW5","../utils/find-spring.mjs":"9Vt1B","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"9Vt1B":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "calcAngularFreq", ()=>calcAngularFreq);
parcelHelpers.export(exports, "findSpring", ()=>findSpring);
parcelHelpers.export(exports, "maxDamping", ()=>maxDamping);
parcelHelpers.export(exports, "maxDuration", ()=>maxDuration);
parcelHelpers.export(exports, "minDamping", ()=>minDamping);
parcelHelpers.export(exports, "minDuration", ()=>minDuration);
var _heyListen = require("hey-listen");
var _clampMjs = require("../../utils/clamp.mjs");
const safeMin = 0.001;
const minDuration = 0.01;
const maxDuration = 10.0;
const minDamping = 0.05;
const maxDamping = 1;
function findSpring({ duration = 800, bounce = 0.25, velocity = 0, mass = 1 }) {
    let envelope;
    let derivative;
    (0, _heyListen.warning)(duration <= maxDuration * 1000, "Spring duration must be 10 seconds or less");
    let dampingRatio = 1 - bounce;
    dampingRatio = (0, _clampMjs.clamp)(minDamping, maxDamping, dampingRatio);
    duration = (0, _clampMjs.clamp)(minDuration, maxDuration, duration / 1000);
    if (dampingRatio < 1) {
        envelope = (undampedFreq)=>{
            const exponentialDecay = undampedFreq * dampingRatio;
            const delta = exponentialDecay * duration;
            const a = exponentialDecay - velocity;
            const b = calcAngularFreq(undampedFreq, dampingRatio);
            const c = Math.exp(-delta);
            return safeMin - a / b * c;
        };
        derivative = (undampedFreq)=>{
            const exponentialDecay = undampedFreq * dampingRatio;
            const delta = exponentialDecay * duration;
            const d = delta * velocity + velocity;
            const e = Math.pow(dampingRatio, 2) * Math.pow(undampedFreq, 2) * duration;
            const f = Math.exp(-delta);
            const g = calcAngularFreq(Math.pow(undampedFreq, 2), dampingRatio);
            const factor = -envelope(undampedFreq) + safeMin > 0 ? -1 : 1;
            return factor * ((d - e) * f) / g;
        };
    } else {
        envelope = (undampedFreq)=>{
            const a = Math.exp(-undampedFreq * duration);
            const b = (undampedFreq - velocity) * duration + 1;
            return -safeMin + a * b;
        };
        derivative = (undampedFreq)=>{
            const a = Math.exp(-undampedFreq * duration);
            const b = (velocity - undampedFreq) * (duration * duration);
            return a * b;
        };
    }
    const initialGuess = 5 / duration;
    const undampedFreq = approximateRoot(envelope, derivative, initialGuess);
    duration = duration * 1000;
    if (isNaN(undampedFreq)) return {
        stiffness: 100,
        damping: 10,
        duration
    };
    else {
        const stiffness = Math.pow(undampedFreq, 2) * mass;
        return {
            stiffness,
            damping: dampingRatio * 2 * Math.sqrt(mass * stiffness),
            duration
        };
    }
}
const rootIterations = 12;
function approximateRoot(envelope, derivative, initialGuess) {
    let result = initialGuess;
    for(let i = 1; i < rootIterations; i++)result = result - envelope(result) / derivative(result);
    return result;
}
function calcAngularFreq(undampedFreq, dampingRatio) {
    return undampedFreq * Math.sqrt(1 - dampingRatio * dampingRatio);
}

},{"hey-listen":"8yK8Z","../../utils/clamp.mjs":"Y4sdh","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"8yK8Z":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "invariant", ()=>invariant);
parcelHelpers.export(exports, "warning", ()=>warning);
var warning = function() {};
var invariant = function() {};
warning = function(check, message) {
    if (!check && typeof console !== "undefined") console.warn(message);
};
invariant = function(check, message) {
    if (!check) throw new Error(message);
};

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"Y4sdh":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "clamp", ()=>clamp);
const clamp = (min, max, v)=>Math.min(Math.max(v, min), max);

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"4AWeA":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "convertOffsetToTimes", ()=>convertOffsetToTimes);
parcelHelpers.export(exports, "defaultEasing", ()=>defaultEasing);
parcelHelpers.export(exports, "defaultOffset", ()=>defaultOffset);
parcelHelpers.export(exports, "keyframes", ()=>keyframes);
var _interpolateMjs = require("../../utils/interpolate.mjs");
var _indexMjs = require("../../easing/index.mjs");
function defaultEasing(values, easing) {
    return values.map(()=>easing || (0, _indexMjs.easeInOut)).splice(0, values.length - 1);
}
function defaultOffset(values) {
    const numValues = values.length;
    return values.map((_value, i)=>i !== 0 ? i / (numValues - 1) : 0);
}
function convertOffsetToTimes(offset, duration) {
    return offset.map((o)=>o * duration);
}
function keyframes({ from = 0, to = 1, ease, offset, duration = 300 }) {
    const state = {
        done: false,
        value: from
    };
    const values = Array.isArray(to) ? to : [
        from,
        to
    ];
    const times = convertOffsetToTimes(offset && offset.length === values.length ? offset : defaultOffset(values), duration);
    function createInterpolator() {
        return (0, _interpolateMjs.interpolate)(times, values, {
            ease: Array.isArray(ease) ? ease : defaultEasing(values, ease)
        });
    }
    let interpolator = createInterpolator();
    return {
        next: (t)=>{
            state.value = interpolator(t);
            state.done = t >= duration;
            return state;
        },
        flipTarget: ()=>{
            values.reverse();
            interpolator = createInterpolator();
        }
    };
}

},{"../../utils/interpolate.mjs":"9axN1","../../easing/index.mjs":"lSPVQ","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"9axN1":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "interpolate", ()=>interpolate);
var _progressMjs = require("./progress.mjs");
var _mixMjs = require("./mix.mjs");
var _mixColorMjs = require("./mix-color.mjs");
var _mixComplexMjs = require("./mix-complex.mjs");
var _styleValueTypes = require("style-value-types");
var _clampMjs = require("./clamp.mjs");
var _pipeMjs = require("./pipe.mjs");
var _heyListen = require("hey-listen");
const mixNumber = (from, to)=>(p)=>(0, _mixMjs.mix)(from, to, p);
function detectMixerFactory(v) {
    if (typeof v === "number") return mixNumber;
    else if (typeof v === "string") {
        if ((0, _styleValueTypes.color).test(v)) return 0, _mixColorMjs.mixColor;
        else return 0, _mixComplexMjs.mixComplex;
    } else if (Array.isArray(v)) return 0, _mixComplexMjs.mixArray;
    else if (typeof v === "object") return 0, _mixComplexMjs.mixObject;
}
function createMixers(output, ease, customMixer) {
    const mixers = [];
    const mixerFactory = customMixer || detectMixerFactory(output[0]);
    const numMixers = output.length - 1;
    for(let i = 0; i < numMixers; i++){
        let mixer = mixerFactory(output[i], output[i + 1]);
        if (ease) {
            const easingFunction = Array.isArray(ease) ? ease[i] : ease;
            mixer = (0, _pipeMjs.pipe)(easingFunction, mixer);
        }
        mixers.push(mixer);
    }
    return mixers;
}
function fastInterpolate([from, to], [mixer]) {
    return (v)=>mixer((0, _progressMjs.progress)(from, to, v));
}
function slowInterpolate(input, mixers) {
    const inputLength = input.length;
    const lastInputIndex = inputLength - 1;
    return (v)=>{
        let mixerIndex = 0;
        let foundMixerIndex = false;
        if (v <= input[0]) foundMixerIndex = true;
        else if (v >= input[lastInputIndex]) {
            mixerIndex = lastInputIndex - 1;
            foundMixerIndex = true;
        }
        if (!foundMixerIndex) {
            let i = 1;
            for(; i < inputLength; i++){
                if (input[i] > v || i === lastInputIndex) break;
            }
            mixerIndex = i - 1;
        }
        const progressInRange = (0, _progressMjs.progress)(input[mixerIndex], input[mixerIndex + 1], v);
        return mixers[mixerIndex](progressInRange);
    };
}
function interpolate(input, output, { clamp: isClamp = true, ease, mixer } = {}) {
    const inputLength = input.length;
    (0, _heyListen.invariant)(inputLength === output.length, "Both input and output ranges must be the same length");
    (0, _heyListen.invariant)(!ease || !Array.isArray(ease) || ease.length === inputLength - 1, "Array of easing functions must be of length `input.length - 1`, as it applies to the transitions **between** the defined values.");
    if (input[0] > input[inputLength - 1]) {
        input = [].concat(input);
        output = [].concat(output);
        input.reverse();
        output.reverse();
    }
    const mixers = createMixers(output, ease, mixer);
    const interpolator = inputLength === 2 ? fastInterpolate(input, mixers) : slowInterpolate(input, mixers);
    return isClamp ? (v)=>interpolator((0, _clampMjs.clamp)(input[0], input[inputLength - 1], v)) : interpolator;
}

},{"./progress.mjs":"d01Ia","./mix.mjs":"23SEC","./mix-color.mjs":"03T1w","./mix-complex.mjs":"bRXYN","style-value-types":"20BqW","./clamp.mjs":"Y4sdh","./pipe.mjs":"hg0kf","hey-listen":"8yK8Z","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"d01Ia":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "progress", ()=>progress);
const progress = (from, to, value)=>{
    const toFromDifference = to - from;
    return toFromDifference === 0 ? 1 : (value - from) / toFromDifference;
};

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"23SEC":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "mix", ()=>mix);
const mix = (from, to, progress)=>-progress * from + progress * to + from;

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"03T1w":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "mixColor", ()=>mixColor);
parcelHelpers.export(exports, "mixLinearColor", ()=>mixLinearColor);
var _mixMjs = require("./mix.mjs");
var _styleValueTypes = require("style-value-types");
var _heyListen = require("hey-listen");
var _hslaToRgbaMjs = require("./hsla-to-rgba.mjs");
const mixLinearColor = (from, to, v)=>{
    const fromExpo = from * from;
    const toExpo = to * to;
    return Math.sqrt(Math.max(0, v * (toExpo - fromExpo) + fromExpo));
};
const colorTypes = [
    (0, _styleValueTypes.hex),
    (0, _styleValueTypes.rgba),
    (0, _styleValueTypes.hsla)
];
const getColorType = (v)=>colorTypes.find((type)=>type.test(v));
const notAnimatable = (color)=>`'${color}' is not an animatable color. Use the equivalent color code instead.`;
const mixColor = (from, to)=>{
    let fromColorType = getColorType(from);
    let toColorType = getColorType(to);
    (0, _heyListen.invariant)(!!fromColorType, notAnimatable(from));
    (0, _heyListen.invariant)(!!toColorType, notAnimatable(to));
    let fromColor = fromColorType.parse(from);
    let toColor = toColorType.parse(to);
    if (fromColorType === (0, _styleValueTypes.hsla)) {
        fromColor = (0, _hslaToRgbaMjs.hslaToRgba)(fromColor);
        fromColorType = (0, _styleValueTypes.rgba);
    }
    if (toColorType === (0, _styleValueTypes.hsla)) {
        toColor = (0, _hslaToRgbaMjs.hslaToRgba)(toColor);
        toColorType = (0, _styleValueTypes.rgba);
    }
    const blended = Object.assign({}, fromColor);
    return (v)=>{
        for(const key in blended)if (key !== "alpha") blended[key] = mixLinearColor(fromColor[key], toColor[key], v);
        blended.alpha = (0, _mixMjs.mix)(fromColor.alpha, toColor.alpha, v);
        return fromColorType.transform(blended);
    };
};

},{"./mix.mjs":"23SEC","style-value-types":"20BqW","hey-listen":"8yK8Z","./hsla-to-rgba.mjs":"5OhyK","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"20BqW":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "alpha", ()=>(0, _indexMjs.alpha));
parcelHelpers.export(exports, "number", ()=>(0, _indexMjs.number));
parcelHelpers.export(exports, "scale", ()=>(0, _indexMjs.scale));
parcelHelpers.export(exports, "degrees", ()=>(0, _unitsMjs.degrees));
parcelHelpers.export(exports, "percent", ()=>(0, _unitsMjs.percent));
parcelHelpers.export(exports, "progressPercentage", ()=>(0, _unitsMjs.progressPercentage));
parcelHelpers.export(exports, "px", ()=>(0, _unitsMjs.px));
parcelHelpers.export(exports, "vh", ()=>(0, _unitsMjs.vh));
parcelHelpers.export(exports, "vw", ()=>(0, _unitsMjs.vw));
parcelHelpers.export(exports, "hsla", ()=>(0, _hslaMjs.hsla));
parcelHelpers.export(exports, "rgbUnit", ()=>(0, _rgbaMjs.rgbUnit));
parcelHelpers.export(exports, "rgba", ()=>(0, _rgbaMjs.rgba));
parcelHelpers.export(exports, "hex", ()=>(0, _hexMjs.hex));
parcelHelpers.export(exports, "color", ()=>(0, _indexMjs1.color));
parcelHelpers.export(exports, "complex", ()=>(0, _indexMjs2.complex));
parcelHelpers.export(exports, "filter", ()=>(0, _filterMjs.filter));
var _indexMjs = require("./numbers/index.mjs");
var _unitsMjs = require("./numbers/units.mjs");
var _hslaMjs = require("./color/hsla.mjs");
var _rgbaMjs = require("./color/rgba.mjs");
var _hexMjs = require("./color/hex.mjs");
var _indexMjs1 = require("./color/index.mjs");
var _indexMjs2 = require("./complex/index.mjs");
var _filterMjs = require("./complex/filter.mjs");

},{"./numbers/index.mjs":false,"./numbers/units.mjs":false,"./color/hsla.mjs":"bnchv","./color/rgba.mjs":"8PKFL","./color/hex.mjs":"91vvA","./color/index.mjs":"2NVB9","./complex/index.mjs":"1RdRB","./complex/filter.mjs":false,"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"f4k82":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "alpha", ()=>alpha);
parcelHelpers.export(exports, "number", ()=>number);
parcelHelpers.export(exports, "scale", ()=>scale);
var _utilsMjs = require("../utils.mjs");
const number = {
    test: (v)=>typeof v === "number",
    parse: parseFloat,
    transform: (v)=>v
};
const alpha = Object.assign(Object.assign({}, number), {
    transform: (0, _utilsMjs.clamp)(0, 1)
});
const scale = Object.assign(Object.assign({}, number), {
    default: 1
});

},{"../utils.mjs":"krEGS","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"krEGS":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "clamp", ()=>clamp);
parcelHelpers.export(exports, "colorRegex", ()=>colorRegex);
parcelHelpers.export(exports, "floatRegex", ()=>floatRegex);
parcelHelpers.export(exports, "isString", ()=>isString);
parcelHelpers.export(exports, "sanitize", ()=>sanitize);
parcelHelpers.export(exports, "singleColorRegex", ()=>singleColorRegex);
const clamp = (min, max)=>(v)=>Math.max(Math.min(v, max), min);
const sanitize = (v)=>v % 1 ? Number(v.toFixed(5)) : v;
const floatRegex = /(-)?([\d]*\.?[\d])+/g;
const colorRegex = /(#[0-9a-f]{6}|#[0-9a-f]{3}|#(?:[0-9a-f]{2}){2,4}|(rgb|hsl)a?\((-?[\d\.]+%?[,\s]+){2}(-?[\d\.]+%?)\s*[\,\/]?\s*[\d\.]*%?\))/gi;
const singleColorRegex = /^(#[0-9a-f]{3}|#(?:[0-9a-f]{2}){2,4}|(rgb|hsl)a?\((-?[\d\.]+%?[,\s]+){2}(-?[\d\.]+%?)\s*[\,\/]?\s*[\d\.]*%?\))$/i;
function isString(v) {
    return typeof v === "string";
}

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"fFU8C":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "degrees", ()=>degrees);
parcelHelpers.export(exports, "percent", ()=>percent);
parcelHelpers.export(exports, "progressPercentage", ()=>progressPercentage);
parcelHelpers.export(exports, "px", ()=>px);
parcelHelpers.export(exports, "vh", ()=>vh);
parcelHelpers.export(exports, "vw", ()=>vw);
var _utilsMjs = require("../utils.mjs");
const createUnitType = (unit)=>({
        test: (v)=>(0, _utilsMjs.isString)(v) && v.endsWith(unit) && v.split(" ").length === 1,
        parse: parseFloat,
        transform: (v)=>`${v}${unit}`
    });
const degrees = createUnitType("deg");
const percent = createUnitType("%");
const px = createUnitType("px");
const vh = createUnitType("vh");
const vw = createUnitType("vw");
const progressPercentage = Object.assign(Object.assign({}, percent), {
    parse: (v)=>percent.parse(v) / 100,
    transform: (v)=>percent.transform(v * 100)
});

},{"../utils.mjs":"krEGS","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"bnchv":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "hsla", ()=>hsla);
var _indexMjs = require("../numbers/index.mjs");
var _unitsMjs = require("../numbers/units.mjs");
var _utilsMjs = require("../utils.mjs");
var _utilsMjs1 = require("./utils.mjs");
const hsla = {
    test: (0, _utilsMjs1.isColorString)("hsl", "hue"),
    parse: (0, _utilsMjs1.splitColor)("hue", "saturation", "lightness"),
    transform: ({ hue, saturation, lightness, alpha: alpha$1 = 1 })=>{
        return "hsla(" + Math.round(hue) + ", " + (0, _unitsMjs.percent).transform((0, _utilsMjs.sanitize)(saturation)) + ", " + (0, _unitsMjs.percent).transform((0, _utilsMjs.sanitize)(lightness)) + ", " + (0, _utilsMjs.sanitize)((0, _indexMjs.alpha).transform(alpha$1)) + ")";
    }
};

},{"../numbers/index.mjs":"f4k82","../numbers/units.mjs":"fFU8C","../utils.mjs":"krEGS","./utils.mjs":"hhRk9","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"hhRk9":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "isColorString", ()=>isColorString);
parcelHelpers.export(exports, "splitColor", ()=>splitColor);
var _utilsMjs = require("../utils.mjs");
const isColorString = (type, testProp)=>(v)=>{
        return Boolean((0, _utilsMjs.isString)(v) && (0, _utilsMjs.singleColorRegex).test(v) && v.startsWith(type) || testProp && Object.prototype.hasOwnProperty.call(v, testProp));
    };
const splitColor = (aName, bName, cName)=>(v)=>{
        if (!(0, _utilsMjs.isString)(v)) return v;
        const [a, b, c, alpha] = v.match((0, _utilsMjs.floatRegex));
        return {
            [aName]: parseFloat(a),
            [bName]: parseFloat(b),
            [cName]: parseFloat(c),
            alpha: alpha !== undefined ? parseFloat(alpha) : 1
        };
    };

},{"../utils.mjs":"krEGS","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"8PKFL":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "rgbUnit", ()=>rgbUnit);
parcelHelpers.export(exports, "rgba", ()=>rgba);
var _indexMjs = require("../numbers/index.mjs");
var _utilsMjs = require("../utils.mjs");
var _utilsMjs1 = require("./utils.mjs");
const clampRgbUnit = (0, _utilsMjs.clamp)(0, 255);
const rgbUnit = Object.assign(Object.assign({}, (0, _indexMjs.number)), {
    transform: (v)=>Math.round(clampRgbUnit(v))
});
const rgba = {
    test: (0, _utilsMjs1.isColorString)("rgb", "red"),
    parse: (0, _utilsMjs1.splitColor)("red", "green", "blue"),
    transform: ({ red, green, blue, alpha: alpha$1 = 1 })=>"rgba(" + rgbUnit.transform(red) + ", " + rgbUnit.transform(green) + ", " + rgbUnit.transform(blue) + ", " + (0, _utilsMjs.sanitize)((0, _indexMjs.alpha).transform(alpha$1)) + ")"
};

},{"../numbers/index.mjs":"f4k82","../utils.mjs":"krEGS","./utils.mjs":"hhRk9","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"91vvA":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "hex", ()=>hex);
var _rgbaMjs = require("./rgba.mjs");
var _utilsMjs = require("./utils.mjs");
function parseHex(v) {
    let r = "";
    let g = "";
    let b = "";
    let a = "";
    if (v.length > 5) {
        r = v.substr(1, 2);
        g = v.substr(3, 2);
        b = v.substr(5, 2);
        a = v.substr(7, 2);
    } else {
        r = v.substr(1, 1);
        g = v.substr(2, 1);
        b = v.substr(3, 1);
        a = v.substr(4, 1);
        r += r;
        g += g;
        b += b;
        a += a;
    }
    return {
        red: parseInt(r, 16),
        green: parseInt(g, 16),
        blue: parseInt(b, 16),
        alpha: a ? parseInt(a, 16) / 255 : 1
    };
}
const hex = {
    test: (0, _utilsMjs.isColorString)("#"),
    parse: parseHex,
    transform: (0, _rgbaMjs.rgba).transform
};

},{"./rgba.mjs":"8PKFL","./utils.mjs":"hhRk9","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"2NVB9":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "color", ()=>color);
var _utilsMjs = require("../utils.mjs");
var _hexMjs = require("./hex.mjs");
var _hslaMjs = require("./hsla.mjs");
var _rgbaMjs = require("./rgba.mjs");
const color = {
    test: (v)=>(0, _rgbaMjs.rgba).test(v) || (0, _hexMjs.hex).test(v) || (0, _hslaMjs.hsla).test(v),
    parse: (v)=>{
        if ((0, _rgbaMjs.rgba).test(v)) return (0, _rgbaMjs.rgba).parse(v);
        else if ((0, _hslaMjs.hsla).test(v)) return (0, _hslaMjs.hsla).parse(v);
        else return (0, _hexMjs.hex).parse(v);
    },
    transform: (v)=>{
        return (0, _utilsMjs.isString)(v) ? v : v.hasOwnProperty("red") ? (0, _rgbaMjs.rgba).transform(v) : (0, _hslaMjs.hsla).transform(v);
    }
};

},{"../utils.mjs":"krEGS","./hex.mjs":"91vvA","./hsla.mjs":"bnchv","./rgba.mjs":"8PKFL","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"1RdRB":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "complex", ()=>complex);
var _indexMjs = require("../color/index.mjs");
var _indexMjs1 = require("../numbers/index.mjs");
var _utilsMjs = require("../utils.mjs");
const colorToken = "${c}";
const numberToken = "${n}";
function test(v) {
    var _a, _b, _c, _d;
    return isNaN(v) && (0, _utilsMjs.isString)(v) && ((_b = (_a = v.match((0, _utilsMjs.floatRegex))) === null || _a === void 0 ? void 0 : _a.length) !== null && _b !== void 0 ? _b : 0) + ((_d = (_c = v.match((0, _utilsMjs.colorRegex))) === null || _c === void 0 ? void 0 : _c.length) !== null && _d !== void 0 ? _d : 0) > 0;
}
function analyse(v) {
    if (typeof v === "number") v = `${v}`;
    const values = [];
    let numColors = 0;
    const colors = v.match((0, _utilsMjs.colorRegex));
    if (colors) {
        numColors = colors.length;
        v = v.replace((0, _utilsMjs.colorRegex), colorToken);
        values.push(...colors.map((0, _indexMjs.color).parse));
    }
    const numbers = v.match((0, _utilsMjs.floatRegex));
    if (numbers) {
        v = v.replace((0, _utilsMjs.floatRegex), numberToken);
        values.push(...numbers.map((0, _indexMjs1.number).parse));
    }
    return {
        values,
        numColors,
        tokenised: v
    };
}
function parse(v) {
    return analyse(v).values;
}
function createTransformer(v) {
    const { values, numColors, tokenised } = analyse(v);
    const numValues = values.length;
    return (v)=>{
        let output = tokenised;
        for(let i = 0; i < numValues; i++)output = output.replace(i < numColors ? colorToken : numberToken, i < numColors ? (0, _indexMjs.color).transform(v[i]) : (0, _utilsMjs.sanitize)(v[i]));
        return output;
    };
}
const convertNumbersToZero = (v)=>typeof v === "number" ? 0 : v;
function getAnimatableNone(v) {
    const parsed = parse(v);
    const transformer = createTransformer(v);
    return transformer(parsed.map(convertNumbersToZero));
}
const complex = {
    test,
    parse,
    createTransformer,
    getAnimatableNone
};

},{"../color/index.mjs":"2NVB9","../numbers/index.mjs":"f4k82","../utils.mjs":"krEGS","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"5OhyK":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "hslaToRgba", ()=>hslaToRgba);
function hueToRgb(p, q, t) {
    if (t < 0) t += 1;
    if (t > 1) t -= 1;
    if (t < 1 / 6) return p + (q - p) * 6 * t;
    if (t < 0.5) return q;
    if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
    return p;
}
function hslaToRgba({ hue, saturation, lightness, alpha }) {
    hue /= 360;
    saturation /= 100;
    lightness /= 100;
    let red = 0;
    let green = 0;
    let blue = 0;
    if (!saturation) red = green = blue = lightness;
    else {
        const q = lightness < 0.5 ? lightness * (1 + saturation) : lightness + saturation - lightness * saturation;
        const p = 2 * lightness - q;
        red = hueToRgb(p, q, hue + 1 / 3);
        green = hueToRgb(p, q, hue);
        blue = hueToRgb(p, q, hue - 1 / 3);
    }
    return {
        red: Math.round(red * 255),
        green: Math.round(green * 255),
        blue: Math.round(blue * 255),
        alpha
    };
}

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"bRXYN":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "mixArray", ()=>mixArray);
parcelHelpers.export(exports, "mixComplex", ()=>mixComplex);
parcelHelpers.export(exports, "mixObject", ()=>mixObject);
var _styleValueTypes = require("style-value-types");
var _mixMjs = require("./mix.mjs");
var _mixColorMjs = require("./mix-color.mjs");
var _incMjs = require("./inc.mjs");
var _pipeMjs = require("./pipe.mjs");
var _heyListen = require("hey-listen");
function getMixer(origin, target) {
    if ((0, _incMjs.isNum)(origin)) return (v)=>(0, _mixMjs.mix)(origin, target, v);
    else if ((0, _styleValueTypes.color).test(origin)) return (0, _mixColorMjs.mixColor)(origin, target);
    else return mixComplex(origin, target);
}
const mixArray = (from, to)=>{
    const output = [
        ...from
    ];
    const numValues = output.length;
    const blendValue = from.map((fromThis, i)=>getMixer(fromThis, to[i]));
    return (v)=>{
        for(let i = 0; i < numValues; i++)output[i] = blendValue[i](v);
        return output;
    };
};
const mixObject = (origin, target)=>{
    const output = Object.assign(Object.assign({}, origin), target);
    const blendValue = {};
    for(const key in output)if (origin[key] !== undefined && target[key] !== undefined) blendValue[key] = getMixer(origin[key], target[key]);
    return (v)=>{
        for(const key in blendValue)output[key] = blendValue[key](v);
        return output;
    };
};
function analyse(value) {
    const parsed = (0, _styleValueTypes.complex).parse(value);
    const numValues = parsed.length;
    let numNumbers = 0;
    let numRGB = 0;
    let numHSL = 0;
    for(let i = 0; i < numValues; i++){
        if (numNumbers || typeof parsed[i] === "number") numNumbers++;
        else if (parsed[i].hue !== undefined) numHSL++;
        else numRGB++;
    }
    return {
        parsed,
        numNumbers,
        numRGB,
        numHSL
    };
}
const mixComplex = (origin, target)=>{
    const template = (0, _styleValueTypes.complex).createTransformer(target);
    const originStats = analyse(origin);
    const targetStats = analyse(target);
    const canInterpolate = originStats.numHSL === targetStats.numHSL && originStats.numRGB === targetStats.numRGB && originStats.numNumbers >= targetStats.numNumbers;
    if (canInterpolate) return (0, _pipeMjs.pipe)(mixArray(originStats.parsed, targetStats.parsed), template);
    else {
        (0, _heyListen.warning)(true, `Complex values '${origin}' and '${target}' too different to mix. Ensure all colors are of the same type, and that each contains the same quantity of number and color values. Falling back to instant transition.`);
        return (p)=>`${p > 0 ? target : origin}`;
    }
};

},{"style-value-types":"20BqW","./mix.mjs":"23SEC","./mix-color.mjs":"03T1w","./inc.mjs":"gaeuJ","./pipe.mjs":"hg0kf","hey-listen":"8yK8Z","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"gaeuJ":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "isNum", ()=>isNum);
parcelHelpers.export(exports, "zeroPoint", ()=>zeroPoint);
const zeroPoint = {
    x: 0,
    y: 0,
    z: 0
};
const isNum = (v)=>typeof v === "number";

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"hg0kf":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "pipe", ()=>pipe);
const combineFunctions = (a, b)=>(v)=>b(a(v));
const pipe = (...transformers)=>transformers.reduce(combineFunctions);

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"lSPVQ":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "anticipate", ()=>anticipate);
parcelHelpers.export(exports, "backIn", ()=>backIn);
parcelHelpers.export(exports, "backInOut", ()=>backInOut);
parcelHelpers.export(exports, "backOut", ()=>backOut);
parcelHelpers.export(exports, "bounceIn", ()=>bounceIn);
parcelHelpers.export(exports, "bounceInOut", ()=>bounceInOut);
parcelHelpers.export(exports, "bounceOut", ()=>bounceOut);
parcelHelpers.export(exports, "circIn", ()=>circIn);
parcelHelpers.export(exports, "circInOut", ()=>circInOut);
parcelHelpers.export(exports, "circOut", ()=>circOut);
parcelHelpers.export(exports, "easeIn", ()=>easeIn);
parcelHelpers.export(exports, "easeInOut", ()=>easeInOut);
parcelHelpers.export(exports, "easeOut", ()=>easeOut);
parcelHelpers.export(exports, "linear", ()=>linear);
var _utilsMjs = require("./utils.mjs");
const DEFAULT_OVERSHOOT_STRENGTH = 1.525;
const BOUNCE_FIRST_THRESHOLD = 4.0 / 11.0;
const BOUNCE_SECOND_THRESHOLD = 8.0 / 11.0;
const BOUNCE_THIRD_THRESHOLD = 0.9;
const linear = (p)=>p;
const easeIn = (0, _utilsMjs.createExpoIn)(2);
const easeOut = (0, _utilsMjs.reverseEasing)(easeIn);
const easeInOut = (0, _utilsMjs.mirrorEasing)(easeIn);
const circIn = (p)=>1 - Math.sin(Math.acos(p));
const circOut = (0, _utilsMjs.reverseEasing)(circIn);
const circInOut = (0, _utilsMjs.mirrorEasing)(circOut);
const backIn = (0, _utilsMjs.createBackIn)(DEFAULT_OVERSHOOT_STRENGTH);
const backOut = (0, _utilsMjs.reverseEasing)(backIn);
const backInOut = (0, _utilsMjs.mirrorEasing)(backIn);
const anticipate = (0, _utilsMjs.createAnticipate)(DEFAULT_OVERSHOOT_STRENGTH);
const ca = 4356.0 / 361.0;
const cb = 35442.0 / 1805.0;
const cc = 16061.0 / 1805.0;
const bounceOut = (p)=>{
    if (p === 1 || p === 0) return p;
    const p2 = p * p;
    return p < BOUNCE_FIRST_THRESHOLD ? 7.5625 * p2 : p < BOUNCE_SECOND_THRESHOLD ? 9.075 * p2 - 9.9 * p + 3.4 : p < BOUNCE_THIRD_THRESHOLD ? ca * p2 - cb * p + cc : 10.8 * p * p - 20.52 * p + 10.72;
};
const bounceIn = (0, _utilsMjs.reverseEasing)(bounceOut);
const bounceInOut = (p)=>p < 0.5 ? 0.5 * (1.0 - bounceOut(1.0 - p * 2.0)) : 0.5 * bounceOut(p * 2.0 - 1.0) + 0.5;

},{"./utils.mjs":"2LkwN","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"2LkwN":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "createAnticipate", ()=>createAnticipate);
parcelHelpers.export(exports, "createBackIn", ()=>createBackIn);
parcelHelpers.export(exports, "createExpoIn", ()=>createExpoIn);
parcelHelpers.export(exports, "mirrorEasing", ()=>mirrorEasing);
parcelHelpers.export(exports, "reverseEasing", ()=>reverseEasing);
const reverseEasing = (easing)=>(p)=>1 - easing(1 - p);
const mirrorEasing = (easing)=>(p)=>p <= 0.5 ? easing(2 * p) / 2 : (2 - easing(2 * (1 - p))) / 2;
const createExpoIn = (power)=>(p)=>Math.pow(p, power);
const createBackIn = (power)=>(p)=>p * p * ((power + 1) * p - power);
const createAnticipate = (power)=>{
    const backEasing = createBackIn(power);
    return (p)=>(p *= 2) < 1 ? 0.5 * backEasing(p) : 0.5 * (2 - Math.pow(2, -10 * (p - 1)));
};

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"apvaq":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "decay", ()=>decay);
function decay({ velocity = 0, from = 0, power = 0.8, timeConstant = 350, restDelta = 0.5, modifyTarget }) {
    const state = {
        done: false,
        value: from
    };
    let amplitude = power * velocity;
    const ideal = from + amplitude;
    const target = modifyTarget === undefined ? ideal : modifyTarget(ideal);
    if (target !== ideal) amplitude = target - from;
    return {
        next: (t)=>{
            const delta = -amplitude * Math.exp(-t / timeConstant);
            state.done = !(delta > restDelta || delta < -restDelta);
            state.value = state.done ? target : target + delta;
            return state;
        },
        flipTarget: ()=>{}
    };
}

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"lhfBw":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "cancelSync", ()=>cancelSync);
parcelHelpers.export(exports, "flushSync", ()=>flushSync);
parcelHelpers.export(exports, "getFrameData", ()=>getFrameData);
var _onNextFrameMjs = require("./on-next-frame.mjs");
var _createRenderStepMjs = require("./create-render-step.mjs");
const maxElapsed = 40;
let useDefaultElapsed = true;
let runNextFrame = false;
let isProcessing = false;
const frame = {
    delta: 0,
    timestamp: 0
};
const stepsOrder = [
    "read",
    "update",
    "preRender",
    "render",
    "postRender"
];
const steps = stepsOrder.reduce((acc, key)=>{
    acc[key] = (0, _createRenderStepMjs.createRenderStep)(()=>runNextFrame = true);
    return acc;
}, {});
const sync = stepsOrder.reduce((acc, key)=>{
    const step = steps[key];
    acc[key] = (process, keepAlive = false, immediate = false)=>{
        if (!runNextFrame) startLoop();
        return step.schedule(process, keepAlive, immediate);
    };
    return acc;
}, {});
const cancelSync = stepsOrder.reduce((acc, key)=>{
    acc[key] = steps[key].cancel;
    return acc;
}, {});
const flushSync = stepsOrder.reduce((acc, key)=>{
    acc[key] = ()=>steps[key].process(frame);
    return acc;
}, {});
const processStep = (stepId)=>steps[stepId].process(frame);
const processFrame = (timestamp)=>{
    runNextFrame = false;
    frame.delta = useDefaultElapsed ? (0, _onNextFrameMjs.defaultTimestep) : Math.max(Math.min(timestamp - frame.timestamp, maxElapsed), 1);
    frame.timestamp = timestamp;
    isProcessing = true;
    stepsOrder.forEach(processStep);
    isProcessing = false;
    if (runNextFrame) {
        useDefaultElapsed = false;
        (0, _onNextFrameMjs.onNextFrame)(processFrame);
    }
};
const startLoop = ()=>{
    runNextFrame = true;
    useDefaultElapsed = true;
    if (!isProcessing) (0, _onNextFrameMjs.onNextFrame)(processFrame);
};
const getFrameData = ()=>frame;
exports.default = sync;

},{"./on-next-frame.mjs":"7pqDN","./create-render-step.mjs":"ix13w","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"7pqDN":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "defaultTimestep", ()=>defaultTimestep);
parcelHelpers.export(exports, "onNextFrame", ()=>onNextFrame);
const defaultTimestep = 1 / 60 * 1000;
const getCurrentTime = typeof performance !== "undefined" ? ()=>performance.now() : ()=>Date.now();
const onNextFrame = typeof window !== "undefined" ? (callback)=>window.requestAnimationFrame(callback) : (callback)=>setTimeout(()=>callback(getCurrentTime()), defaultTimestep);

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"ix13w":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "createRenderStep", ()=>createRenderStep);
function createRenderStep(runNextFrame) {
    let toRun = [];
    let toRunNextFrame = [];
    let numToRun = 0;
    let isProcessing = false;
    let flushNextFrame = false;
    const toKeepAlive = new WeakSet();
    const step = {
        schedule: (callback, keepAlive = false, immediate = false)=>{
            const addToCurrentFrame = immediate && isProcessing;
            const buffer = addToCurrentFrame ? toRun : toRunNextFrame;
            if (keepAlive) toKeepAlive.add(callback);
            if (buffer.indexOf(callback) === -1) {
                buffer.push(callback);
                if (addToCurrentFrame && isProcessing) numToRun = toRun.length;
            }
            return callback;
        },
        cancel: (callback)=>{
            const index = toRunNextFrame.indexOf(callback);
            if (index !== -1) toRunNextFrame.splice(index, 1);
            toKeepAlive.delete(callback);
        },
        process: (frameData)=>{
            if (isProcessing) {
                flushNextFrame = true;
                return;
            }
            isProcessing = true;
            [toRun, toRunNextFrame] = [
                toRunNextFrame,
                toRun
            ];
            toRunNextFrame.length = 0;
            numToRun = toRun.length;
            if (numToRun) for(let i = 0; i < numToRun; i++){
                const callback = toRun[i];
                callback(frameData);
                if (toKeepAlive.has(callback)) {
                    step.schedule(callback);
                    runNextFrame();
                }
            }
            isProcessing = false;
            if (flushNextFrame) {
                flushNextFrame = false;
                step.process(frameData);
            }
        }
    };
    return step;
}

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"bYEeZ":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "hasRepeatDelayElapsed", ()=>hasRepeatDelayElapsed);
parcelHelpers.export(exports, "loopElapsed", ()=>loopElapsed);
parcelHelpers.export(exports, "reverseElapsed", ()=>reverseElapsed);
function loopElapsed(elapsed, duration, delay = 0) {
    return elapsed - duration - delay;
}
function reverseElapsed(elapsed, duration, delay = 0, isForwardPlayback = true) {
    return isForwardPlayback ? loopElapsed(duration + -elapsed, duration, delay) : duration - (elapsed - duration) + delay;
}
function hasRepeatDelayElapsed(elapsed, duration, delay, isForwardPlayback) {
    return isForwardPlayback ? elapsed >= duration + delay : elapsed <= -delay;
}

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"dSGIQ":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "inertia", ()=>inertia);
var _indexMjs = require("./index.mjs");
var _velocityPerSecondMjs = require("../utils/velocity-per-second.mjs");
var _framesync = require("framesync");
function inertia({ from = 0, velocity = 0, min, max, power = 0.8, timeConstant = 750, bounceStiffness = 500, bounceDamping = 10, restDelta = 1, modifyTarget, driver, onUpdate, onComplete, onStop }) {
    let currentAnimation;
    function isOutOfBounds(v) {
        return min !== undefined && v < min || max !== undefined && v > max;
    }
    function boundaryNearest(v) {
        if (min === undefined) return max;
        if (max === undefined) return min;
        return Math.abs(min - v) < Math.abs(max - v) ? min : max;
    }
    function startAnimation(options) {
        currentAnimation === null || currentAnimation === void 0 || currentAnimation.stop();
        currentAnimation = (0, _indexMjs.animate)(Object.assign(Object.assign({}, options), {
            driver,
            onUpdate: (v)=>{
                var _a;
                onUpdate === null || onUpdate === void 0 || onUpdate(v);
                (_a = options.onUpdate) === null || _a === void 0 || _a.call(options, v);
            },
            onComplete,
            onStop
        }));
    }
    function startSpring(options) {
        startAnimation(Object.assign({
            type: "spring",
            stiffness: bounceStiffness,
            damping: bounceDamping,
            restDelta
        }, options));
    }
    if (isOutOfBounds(from)) startSpring({
        from,
        velocity,
        to: boundaryNearest(from)
    });
    else {
        let target = power * velocity + from;
        if (typeof modifyTarget !== "undefined") target = modifyTarget(target);
        const boundary = boundaryNearest(target);
        const heading = boundary === min ? -1 : 1;
        let prev;
        let current;
        const checkBoundary = (v)=>{
            prev = current;
            current = v;
            velocity = (0, _velocityPerSecondMjs.velocityPerSecond)(v - prev, (0, _framesync.getFrameData)().delta);
            if (heading === 1 && v > boundary || heading === -1 && v < boundary) startSpring({
                from: v,
                to: boundary,
                velocity
            });
        };
        startAnimation({
            type: "decay",
            from,
            velocity,
            timeConstant,
            power,
            restDelta,
            modifyTarget,
            onUpdate: isOutOfBounds(target) ? checkBoundary : undefined
        });
    }
    return {
        stop: ()=>currentAnimation === null || currentAnimation === void 0 ? void 0 : currentAnimation.stop()
    };
}

},{"./index.mjs":"a5fCk","../utils/velocity-per-second.mjs":"2WHye","framesync":"lhfBw","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"2WHye":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "velocityPerSecond", ()=>velocityPerSecond);
function velocityPerSecond(velocity, frameDuration) {
    return frameDuration ? velocity * (1000 / frameDuration) : 0;
}

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"bOLME":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "angle", ()=>angle);
var _radiansToDegreesMjs = require("./radians-to-degrees.mjs");
var _incMjs = require("./inc.mjs");
const angle = (a, b = (0, _incMjs.zeroPoint))=>(0, _radiansToDegreesMjs.radiansToDegrees)(Math.atan2(b.y - a.y, b.x - a.x));

},{"./radians-to-degrees.mjs":"g2UIl","./inc.mjs":"gaeuJ","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"g2UIl":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "radiansToDegrees", ()=>radiansToDegrees);
const radiansToDegrees = (radians)=>radians * 180 / Math.PI;

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"lKx1t":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "applyOffset", ()=>applyOffset);
const applyOffset = (from, to)=>{
    let hasReceivedFrom = true;
    if (to === undefined) {
        to = from;
        hasReceivedFrom = false;
    }
    return (v)=>{
        if (hasReceivedFrom) return v - from + to;
        else {
            from = v;
            hasReceivedFrom = true;
            return to;
        }
    };
};

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"cWCzY":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "attract", ()=>attract);
parcelHelpers.export(exports, "attractExpo", ()=>attractExpo);
parcelHelpers.export(exports, "createAttractor", ()=>createAttractor);
const identity = (v)=>v;
const createAttractor = (alterDisplacement = identity)=>(constant, origin, v)=>{
        const displacement = origin - v;
        const springModifiedDisplacement = -(0 - constant + 1) * (0 - alterDisplacement(Math.abs(displacement)));
        return displacement <= 0 ? origin + springModifiedDisplacement : origin - springModifiedDisplacement;
    };
const attract = createAttractor();
const attractExpo = createAttractor(Math.sqrt);

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"jBUWN":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "degreesToRadians", ()=>degreesToRadians);
const degreesToRadians = (degrees)=>degrees * Math.PI / 180;

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"9yHdu":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "distance", ()=>distance);
var _isPointMjs = require("./is-point.mjs");
var _isPoint3DMjs = require("./is-point-3d.mjs");
var _incMjs = require("./inc.mjs");
const distance1D = (a, b)=>Math.abs(a - b);
function distance(a, b) {
    if ((0, _incMjs.isNum)(a) && (0, _incMjs.isNum)(b)) return distance1D(a, b);
    else if ((0, _isPointMjs.isPoint)(a) && (0, _isPointMjs.isPoint)(b)) {
        const xDelta = distance1D(a.x, b.x);
        const yDelta = distance1D(a.y, b.y);
        const zDelta = (0, _isPoint3DMjs.isPoint3D)(a) && (0, _isPoint3DMjs.isPoint3D)(b) ? distance1D(a.z, b.z) : 0;
        return Math.sqrt(Math.pow(xDelta, 2) + Math.pow(yDelta, 2) + Math.pow(zDelta, 2));
    }
}

},{"./is-point.mjs":"8eQlh","./is-point-3d.mjs":"immOm","./inc.mjs":"gaeuJ","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"8eQlh":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "isPoint", ()=>isPoint);
const isPoint = (point)=>point.hasOwnProperty("x") && point.hasOwnProperty("y");

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"immOm":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "isPoint3D", ()=>isPoint3D);
var _isPointMjs = require("./is-point.mjs");
const isPoint3D = (point)=>(0, _isPointMjs.isPoint)(point) && point.hasOwnProperty("z");

},{"./is-point.mjs":"8eQlh","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"7GM9Y":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "pointFromVector", ()=>pointFromVector);
var _degreesToRadiansMjs = require("./degrees-to-radians.mjs");
const pointFromVector = (origin, angle, distance)=>{
    angle = (0, _degreesToRadiansMjs.degreesToRadians)(angle);
    return {
        x: distance * Math.cos(angle) + origin.x,
        y: distance * Math.sin(angle) + origin.y
    };
};

},{"./degrees-to-radians.mjs":"jBUWN","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"54WVZ":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "smoothFrame", ()=>smoothFrame);
var _toDecimalMjs = require("./to-decimal.mjs");
const smoothFrame = (prevValue, nextValue, duration, smoothing = 0)=>(0, _toDecimalMjs.toDecimal)(prevValue + duration * (nextValue - prevValue) / Math.max(smoothing, duration));

},{"./to-decimal.mjs":"irLx9","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"irLx9":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "toDecimal", ()=>toDecimal);
const toDecimal = (num, precision = 2)=>{
    precision = Math.pow(10, precision);
    return Math.round(num * precision) / precision;
};

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"ctKTV":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "smooth", ()=>smooth);
var _smoothFrameMjs = require("./smooth-frame.mjs");
var _framesync = require("framesync");
const smooth = (strength = 50)=>{
    let previousValue = 0;
    let lastUpdated = 0;
    return (v)=>{
        const currentFramestamp = (0, _framesync.getFrameData)().timestamp;
        const timeDelta = currentFramestamp !== lastUpdated ? currentFramestamp - lastUpdated : 0;
        const newValue = timeDelta ? (0, _smoothFrameMjs.smoothFrame)(previousValue, v, timeDelta, strength) : previousValue;
        lastUpdated = currentFramestamp;
        previousValue = newValue;
        return newValue;
    };
};

},{"./smooth-frame.mjs":"54WVZ","framesync":"lhfBw","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"8RBoK":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "snap", ()=>snap);
const snap = (points)=>{
    if (typeof points === "number") return (v)=>Math.round(v / points) * points;
    else {
        let i = 0;
        const numPoints = points.length;
        return (v)=>{
            let lastDistance = Math.abs(points[0] - v);
            for(i = 1; i < numPoints; i++){
                const point = points[i];
                const distance = Math.abs(point - v);
                if (distance === 0) return point;
                if (distance > lastDistance) return points[i - 1];
                if (i === numPoints - 1) return point;
                lastDistance = distance;
            }
        };
    }
};

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"jKe2m":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "velocityPerFrame", ()=>velocityPerFrame);
function velocityPerFrame(xps, frameDuration) {
    return xps / (1000 / frameDuration);
}

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"aG282":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "wrap", ()=>wrap);
const wrap = (min, max, v)=>{
    const rangeSize = max - min;
    return ((v - min) % rangeSize + rangeSize) % rangeSize + min;
};

},{"@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"7SHvB":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "cubicBezier", ()=>cubicBezier);
var _indexMjs = require("./index.mjs");
const a = (a1, a2)=>1.0 - 3.0 * a2 + 3.0 * a1;
const b = (a1, a2)=>3.0 * a2 - 6.0 * a1;
const c = (a1)=>3.0 * a1;
const calcBezier = (t, a1, a2)=>((a(a1, a2) * t + b(a1, a2)) * t + c(a1)) * t;
const getSlope = (t, a1, a2)=>3.0 * a(a1, a2) * t * t + 2.0 * b(a1, a2) * t + c(a1);
const subdivisionPrecision = 0.0000001;
const subdivisionMaxIterations = 10;
function binarySubdivide(aX, aA, aB, mX1, mX2) {
    let currentX;
    let currentT;
    let i = 0;
    do {
        currentT = aA + (aB - aA) / 2.0;
        currentX = calcBezier(currentT, mX1, mX2) - aX;
        if (currentX > 0.0) aB = currentT;
        else aA = currentT;
    }while (Math.abs(currentX) > subdivisionPrecision && ++i < subdivisionMaxIterations);
    return currentT;
}
const newtonIterations = 8;
const newtonMinSlope = 0.001;
function newtonRaphsonIterate(aX, aGuessT, mX1, mX2) {
    for(let i = 0; i < newtonIterations; ++i){
        const currentSlope = getSlope(aGuessT, mX1, mX2);
        if (currentSlope === 0.0) return aGuessT;
        const currentX = calcBezier(aGuessT, mX1, mX2) - aX;
        aGuessT -= currentX / currentSlope;
    }
    return aGuessT;
}
const kSplineTableSize = 11;
const kSampleStepSize = 1.0 / (kSplineTableSize - 1.0);
function cubicBezier(mX1, mY1, mX2, mY2) {
    if (mX1 === mY1 && mX2 === mY2) return 0, _indexMjs.linear;
    const sampleValues = new Float32Array(kSplineTableSize);
    for(let i = 0; i < kSplineTableSize; ++i)sampleValues[i] = calcBezier(i * kSampleStepSize, mX1, mX2);
    function getTForX(aX) {
        let intervalStart = 0.0;
        let currentSample = 1;
        const lastSample = kSplineTableSize - 1;
        for(; currentSample !== lastSample && sampleValues[currentSample] <= aX; ++currentSample)intervalStart += kSampleStepSize;
        --currentSample;
        const dist = (aX - sampleValues[currentSample]) / (sampleValues[currentSample + 1] - sampleValues[currentSample]);
        const guessForT = intervalStart + dist * kSampleStepSize;
        const initialSlope = getSlope(guessForT, mX1, mX2);
        if (initialSlope >= newtonMinSlope) return newtonRaphsonIterate(aX, guessForT, mX1, mX2);
        else if (initialSlope === 0.0) return guessForT;
        else return binarySubdivide(aX, intervalStart, intervalStart + kSampleStepSize, mX1, mX2);
    }
    return (t)=>t === 0 || t === 1 ? t : calcBezier(getTForX(t), mY1, mY2);
}

},{"./index.mjs":"lSPVQ","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}],"fQk8J":[function(require,module,exports) {
var parcelHelpers = require("@parcel/transformer-js/src/esmodule-helpers.js");
parcelHelpers.defineInteropFlag(exports);
parcelHelpers.export(exports, "steps", ()=>steps);
var _clampMjs = require("../utils/clamp.mjs");
const steps = (steps, direction = "end")=>(progress)=>{
        progress = direction === "end" ? Math.min(progress, 0.999) : Math.max(progress, 0.001);
        const expanded = progress * steps;
        const rounded = direction === "end" ? Math.floor(expanded) : Math.ceil(expanded);
        return (0, _clampMjs.clamp)(0, 1, rounded / steps);
    };

},{"../utils/clamp.mjs":"Y4sdh","@parcel/transformer-js/src/esmodule-helpers.js":"61w1T"}]},["1Jmog","fdzCV"], "fdzCV", "parcelRequire94c2")

//# sourceMappingURL=index.e305f15c.js.map
