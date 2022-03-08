import { CircularProgress } from "@mui/material";
import React, { useEffect, useState } from "react";
import { FormattedMessage } from "react-intl";
import Button from "../components/Button";
import ApiService from "../service/ApiService";

function MonitorView() {
  const [config, setConfig] = useState({});
  const [status, setStatus] = useState({});

  const [loading, setLoading] = useState(true);

  const [softLoading, setSoftLoading] = useState(false);

  useEffect(() => {
    ApiService.fetch("/config", "GET").then((r) => {
      setConfig(r);
      setLoading(false);
    });

    const fetchStatus = async () => {
      while (true) {
        setSoftLoading(true);
        await ApiService.fetch("/status", "GET").then(setStatus);
        setSoftLoading(false);
        await new Promise((r) => setTimeout(r, 500));
      }
    };

    fetchStatus();
  }, []);

  return (
    <>
      <h1 className="text-4xl font-bold">
        <FormattedMessage id={"Monitoring"} defaultMessage={"Monitoring"} />
      </h1>

      {loading && (
        <>
          <div className="grid gap-4 mt-4 items-left text-left mx-auto">
            <CircularProgress color="warning" />
          </div>
        </>
      )}

      {!loading && (
        <div className="grid w-1/2 gap-4 mt-16 mx-auto">
          <code>{JSON.stringify(config, null, 2)}</code>
          <code>{JSON.stringify(status, null, 2)}</code>
        </div>
      )}

      <a
        href="/"
        className="hover:scale-105 transition-all mt-6 hover:text-red-600 text-red-400 font-bold underline"
      >
        <FormattedMessage defaultMessage={"Go back"} id={"Go back"} />
      </a>

      {softLoading && (
         <>
         <div className="grid gap-4 mt-4 items-left text-left mx-auto">
           <CircularProgress color="warning" />
         </div>
       </>
      )}
    </>
  );
}

export default MonitorView;
