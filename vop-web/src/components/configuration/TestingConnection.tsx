import { CircularProgress } from "@mui/material";
import { useEffect, useState } from "react";
import { FormattedMessage } from "react-intl";
import ApiService from "../../service/ApiService";

export interface TestingConnection {
  onContinue: () => void;
}

export default function TestingConnection(props: TestingConnection) {
  const [canContinue, setCanContinue] = useState<boolean>(true);

  const [status, setStatus] = useState<any>("");

  useEffect(() => {
    const interval = setInterval(() => {
      ApiService.fetch("/config/status", "GET").then(setStatus);
    }, 5000);
  }, []);

  useEffect(() => {
    console.log(status, status["configStatus"]);
    if (status["configStatus"] == "8") {
      window.location.href = "#/restart";
    }
  }, [status]);

  return (
    <>
      <p className="mt-4 text-2xl font-bold">
        <FormattedMessage defaultMessage={"Hang on!"} id={"Hang on!"} />
      </p>

      <div className="grid w-1/2 gap-4 mt-4 items-left text-left mx-auto">
        <p className="mx-auto">
          {status["configStatus"] == "0" && <></>}
          {status["configStatus"] == "1" && (
            <FormattedMessage
              defaultMessage={
                "We have sent the config. Waiting for confirmation..."
              }
              id={"We have sent the config. Waiting for confirmation..."}
            />
          )}
          {status["configStatus"] == "2" && <></>}
          {status["configStatus"] == "3" && <></>}
          {status["configStatus"] == "4" && (
            <FormattedMessage
              defaultMessage={"We are currently testing the link..."}
              id={"We are currently testing the link..."}
            />
          )}
          {status["configStatus"] == "5" && (
            <FormattedMessage
              defaultMessage={
                "Something went wrong! Please cancel and try again"
              }
              id={"Something went wrong! Please cancel and try again"}
            />
          )}
          {status["configStatus"] == "6" && <></>}
          {status["configStatus"] == "7" && <></>}
          {status["configStatus"] == "8" && (
            <FormattedMessage defaultMessage={"Done!"} id={"Done!"} />
          )}
          {status["configStatus"] == "9" && <></>}
        </p>
        <div className="grid gap-4 mt-4 items-left text-left mx-auto">
          <CircularProgress color="warning" />
        </div>
      </div>
    </>
  );
}
