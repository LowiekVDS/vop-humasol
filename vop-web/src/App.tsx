import "@ionic/react/css/core.css";
import { HashRouter, Link, Route, Routes } from "react-router-dom";
import "./App.css";
import Header from "./components/Header";
import MainView from "./views/Main";
import PageNotFound from "./views/PageNotFound";
import React from "react";
import "./index.css";
import Configure from "./views/Configure";
import Monitor from "./views/Monitor";

function App() {
  return (
    <div className="App">
      <Header />

      <div className="w-1/2 mx-auto mt-16 flex-grow grid text-center">
        <HashRouter>
          <Routes>
            <Route path="/" element={<MainView />} />
            <Route path="/monitor" element={<Monitor/>} />
            <Route path="/configure" element={<Configure/>} />
            <Route path="*" element={<PageNotFound />} />
          </Routes>
        </HashRouter>
      </div>
    </div>
  );
}

export default App;
