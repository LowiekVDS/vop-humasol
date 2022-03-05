import "@ionic/react/css/core.css";
import { HashRouter, Link, Route, Routes } from "react-router-dom";
import "./App.css";
import Header from "./components/Header";
import MainView from "./views/Main";
import PageNotFound from "./views/PageNotFound";
import React from "react";

function App() {
  return (
    <div className="App">
      <Header />

      <div className="w-1/2 mx-auto mt-16 flex-grow grid text-center">
        <HashRouter>
          <Routes>
            <Route path="/" element={<MainView />} />
            <Route path="*" element={<PageNotFound />} />
          </Routes>
        </HashRouter>
      </div>
    </div>
  );
}

export default App;
